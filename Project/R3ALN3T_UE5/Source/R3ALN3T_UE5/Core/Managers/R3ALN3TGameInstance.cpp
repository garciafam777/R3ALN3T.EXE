#include "R3ALN3TGameInstance.h"
#include "../../Gameplay/Battle/R3ALN3T_BattleManager.h" // Gap D: UR3ALN3T_BattleManager (RunEnemySoulSequence / RunSoulRoundTrip)
#include "../../Gameplay/Narrative/NarrativeManager.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

UR3ALN3TGameInstance::UR3ALN3TGameInstance()
{
}

void UR3ALN3TGameInstance::Init()
{
	Super::Init();

	// Initialize the narrative manager
	NarrativeManager = NewObject<UNarrativeManager>(this, TEXT("NarrativeManager"));

	// Spawn the backend bridge (lives for the app lifetime; talks to local FastAPI on :8000)
	BackendClient = GetWorld()->SpawnActor<ABackendClient>();
	if (!BackendClient)
	{
		UE_LOG(LogTemp, Warning, TEXT("[R3ALN3TGameInstance] Failed to spawn BackendClient"));
	}

	// Gap D: seed persistent souls on a fresh run. Player + 3 NetPs (Trinity/Tyranny/
	// Eternity) all start at 50 (Cracked) for the first build; canon baselines are a
	// cheap per-NetP data change once the story places them. Idempotent: only seed if
	// the roster is empty so a loaded run keeps its saved souls.
	if (CurrentRun.NetPSouls.Num() == 0)
	{
		// Player starts neutral (Cracked, mid-scale) — the band is earned in play.
		CurrentRun.PlayerSoul.Soul = 50.f;

		// Canon NetP starting bands (0=Radiant .. 100=Corrupted):
		//   Trinity  -> Serene   (20) : harmonic/moral anchor of the trinity, grace-leaning.
		//   Tyranny  -> Twisted  (78) : domination corrupts; near the edge, not yet lost.
		//   Eternity -> Fractured(60) : seam-walker, caught between transcendence & collapse.
		struct FSeed { const TCHAR* Name; float Soul; };
		static const FSeed Seeds[] = {
			{ TEXT("Trinity"),  20.f },
			{ TEXT("Tyranny"),  78.f },
			{ TEXT("Eternity"), 60.f },
		};
		for (const FSeed& S : Seeds)
		{
			FCompanionSoul C;
			C.NetPID = S.Name;
			C.Soul.Soul = S.Soul;
			CurrentRun.NetPSouls.Add(C);
		}
		UE_LOG(LogTemp, Log, TEXT("[GAPD-INIT] Seeded player @ 50 (Cracked); ")
			TEXT("Trinity @ 20 (Serene), Tyranny @ 78 (Twisted), Eternity @ 60 (Fractured)"));
	}
}

FString UR3ALN3TGameInstance::GetSavePath(int32 SlotIndex) const
{
	return FPaths::ProjectSavedDir() / TEXT("SaveGames") / FString::Printf(TEXT("slot_%02d.json"), SlotIndex);
}

static TSharedPtr<FJsonObject> RunStateToJson(const FMythosRunState& State)
{
	TSharedPtr<FJsonObject> J = MakeShareable(new FJsonObject());
	J->SetStringField(TEXT("OperatorName"), State.OperatorName);
	J->SetNumberField(TEXT("Career"), static_cast<int32>(State.Career));
	J->SetNumberField(TEXT("Element"), static_cast<int32>(State.Element));
	J->SetNumberField(TEXT("Screen"), static_cast<int32>(State.Screen));
	J->SetNumberField(TEXT("Day"), State.Day);
	J->SetNumberField(TEXT("ActIndex"), State.ActIndex);
	J->SetNumberField(TEXT("Rank"), State.Rank);
	J->SetNumberField(TEXT("HP"), State.HP);
	J->SetNumberField(TEXT("MaxHP"), State.MaxHP);
	J->SetNumberField(TEXT("Attack"), State.Attack);
	J->SetNumberField(TEXT("Tech"), State.Tech);
	J->SetNumberField(TEXT("Shield"), State.Shield);
	J->SetNumberField(TEXT("Z"), State.Z);
	J->SetNumberField(TEXT("Corruption"), State.Corruption);
	J->SetNumberField(TEXT("NetPBond"), State.NetPBond);
	J->SetNumberField(TEXT("Celestial"), State.Celestial);
	J->SetNumberField(TEXT("Aegis"), State.Aegis);
	J->SetNumberField(TEXT("Dominion"), State.Dominion);
	J->SetNumberField(TEXT("Undernet"), State.Undernet);
	J->SetNumberField(TEXT("Abyssal"), State.Abyssal);
	J->SetNumberField(TEXT("FreeGrid"), State.FreeGrid);
	J->SetStringField(TEXT("Objective"), State.Objective);
	J->SetStringField(TEXT("EndingName"), State.EndingName);
	return J;
}

static bool JsonToRunState(const TSharedPtr<FJsonObject>& J, FMythosRunState& Out)
{
	if (!J.IsValid()) return false;

	auto SafeStr = [&](const FString& Key, const FString& Default = TEXT("")) -> FString {
		FString Val;
		return J->TryGetStringField(Key, Val) ? Val : Default;
	};
	auto SafeInt = [&](const FString& Key, int32 Default = 0) -> int32 {
		double Val;
		return J->TryGetNumberField(Key, Val) ? static_cast<int32>(Val) : Default;
	};

	Out.OperatorName = SafeStr(TEXT("OperatorName"), TEXT("MCADMIN?"));
	Out.Career = static_cast<EMythosCareer>(SafeInt(TEXT("Career")));
	Out.Element = static_cast<EMythosElement>(SafeInt(TEXT("Element")));
	Out.Screen = static_cast<EMythosScreen>(SafeInt(TEXT("Screen")));
	Out.Day = SafeInt(TEXT("Day"), 1);
	Out.ActIndex = SafeInt(TEXT("ActIndex"));
	Out.Rank = SafeInt(TEXT("Rank"));
	Out.HP = SafeInt(TEXT("HP"), 30);
	Out.MaxHP = SafeInt(TEXT("MaxHP"), 30);
	Out.Attack = SafeInt(TEXT("Attack"), 6);
	Out.Tech = SafeInt(TEXT("Tech"), 2);
	Out.Shield = SafeInt(TEXT("Shield"));
	Out.Z = SafeInt(TEXT("Z"), 500);
	Out.Corruption = SafeInt(TEXT("Corruption"));
	Out.NetPBond = SafeInt(TEXT("NetPBond"));
	Out.Celestial = SafeInt(TEXT("Celestial"));
	Out.Aegis = SafeInt(TEXT("Aegis"));
	Out.Dominion = SafeInt(TEXT("Dominion"));
	Out.Undernet = SafeInt(TEXT("Undernet"));
	Out.Abyssal = SafeInt(TEXT("Abyssal"));
	Out.FreeGrid = SafeInt(TEXT("FreeGrid"));
	Out.Objective = SafeStr(TEXT("Objective"));
	Out.EndingName = SafeStr(TEXT("EndingName"));
	return true;
}

void UR3ALN3TGameInstance::SaveGame(int32 SlotIndex)
{
	if (SlotIndex < 0 || SlotIndex >= MaxSaveSlots) return;

	const FString FilePath = GetSavePath(SlotIndex);

	TSharedPtr<FJsonObject> Root = MakeShareable(new FJsonObject());
	Root->SetObjectField(TEXT("RunState"), RunStateToJson(CurrentRun.RunState));
	Root->SetNumberField(TEXT("ActiveStoryNodeIndex"), CurrentRun.ActiveStoryNodeIndex);

	TArray<TSharedPtr<FJsonValue>> InvArray;
	for (const FString& Item : CurrentRun.Inventory)
	{
		InvArray.Add(MakeShareable(new FJsonValueString(Item)));
	}
	Root->SetArrayField(TEXT("Inventory"), InvArray);

	// Gap D: persist souls (player + companion roster).
	TSharedPtr<FJsonObject> Souls = MakeShareable(new FJsonObject());
	Souls->SetNumberField(TEXT("PlayerSoul"), CurrentRun.PlayerSoul.Soul);
	TArray<TSharedPtr<FJsonValue>> NetPArr;
	for (const FCompanionSoul& C : CurrentRun.NetPSouls)
	{
		TSharedPtr<FJsonObject> Cj = MakeShareable(new FJsonObject());
		Cj->SetStringField(TEXT("NetPID"), C.NetPID.ToString());
		Cj->SetNumberField(TEXT("Soul"), C.Soul.Soul);
		NetPArr.Add(MakeShareable(new FJsonValueObject(Cj)));
	}
	Souls->SetArrayField(TEXT("NetPSouls"), NetPArr);
	Root->SetObjectField(TEXT("Souls"), Souls);

	FString OutputString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(Root.ToSharedRef(), Writer);

	FFileHelper::SaveStringToFile(OutputString, *FilePath, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
	UE_LOG(LogTemp, Log, TEXT("SaveGame: slot %d written to %s"), SlotIndex, *FilePath);
}

bool UR3ALN3TGameInstance::LoadGame(int32 SlotIndex)
{
	if (SlotIndex < 0 || SlotIndex >= MaxSaveSlots) return false;

	const FString FilePath = GetSavePath(SlotIndex);
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
	{
		UE_LOG(LogTemp, Warning, TEXT("LoadGame: slot %d file not found"), SlotIndex);
		return false;
	}

	FString InputString;
	if (!FFileHelper::LoadFileToString(InputString, *FilePath))
	{
		return false;
	}

	TSharedPtr<FJsonObject> Root = MakeShareable(new FJsonObject());
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(InputString);
	if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid())
	{
		return false;
	}

	FPersistentRunData Data;
	if (!JsonToRunState(Root->GetObjectField(TEXT("RunState")), Data.RunState))
	{
		return false;
	}
	Data.ActiveStoryNodeIndex = Root->GetIntegerField(TEXT("ActiveStoryNodeIndex"));

	const TArray<TSharedPtr<FJsonValue>>* InvArray;
	if (Root->TryGetArrayField(TEXT("Inventory"), InvArray))
	{
		for (const TSharedPtr<FJsonValue>& Val : *InvArray)
		{
			Data.Inventory.Add(Val->AsString());
		}
	}

	// Gap D: restore souls if present (tolerate old saves without the field).
	const TSharedPtr<FJsonObject>* SoulsObj;
	if (Root->TryGetObjectField(TEXT("Souls"), SoulsObj) && SoulsObj->IsValid())
	{
		double PS = 0.0;
		if ((*SoulsObj)->TryGetNumberField(TEXT("PlayerSoul"), PS))
		{
			Data.PlayerSoul.Soul = FMath::Clamp(static_cast<float>(PS), 0.f, 100.f);
		}
		const TArray<TSharedPtr<FJsonValue>>* NetPArr;
		if ((*SoulsObj)->TryGetArrayField(TEXT("NetPSouls"), NetPArr))
		{
			for (const TSharedPtr<FJsonValue>& Val : *NetPArr)
			{
				const TSharedPtr<FJsonObject>* Cj;
				if (Val->TryGetObject(Cj) && Cj->IsValid())
				{
					FCompanionSoul C;
					C.NetPID = FName((*Cj)->GetStringField(TEXT("NetPID")));
					double CS = 50.0;
					if ((*Cj)->TryGetNumberField(TEXT("Soul"), CS))
					{
						C.Soul.Soul = FMath::Clamp(static_cast<float>(CS), 0.f, 100.f);
					}
					Data.NetPSouls.Add(C);
				}
			}
		}
	}

	CurrentRun = Data;
	UE_LOG(LogTemp, Log, TEXT("LoadGame: slot %d loaded successfully"), SlotIndex);
	return true;
}

TArray<FPersistentRunData> UR3ALN3TGameInstance::GetAllSavePreviews() const
{
	TArray<FPersistentRunData> Previews;
	for (int32 i = 0; i < MaxSaveSlots; ++i)
	{
		const FString FilePath = GetSavePath(i);
		if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
		{
			continue;
		}

		FString InputString;
		if (!FFileHelper::LoadFileToString(InputString, *FilePath))
		{
			continue;
		}

		TSharedPtr<FJsonObject> Root = MakeShareable(new FJsonObject());
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(InputString);
		if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid())
		{
			continue;
		}

		FPersistentRunData Data;
		if (JsonToRunState(Root->GetObjectField(TEXT("RunState")), Data.RunState))
		{
			Data.ActiveStoryNodeIndex = Root->GetIntegerField(TEXT("ActiveStoryNodeIndex"));
			Previews.Add(Data);
		}
	}
	return Previews;
}

bool UR3ALN3TGameInstance::HasSaveData(int32 SlotIndex) const
{
	const FString FilePath = GetSavePath(SlotIndex);
	return FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath);
}

void UR3ALN3TGameInstance::DeleteSave(int32 SlotIndex)
{
	const FString FilePath = GetSavePath(SlotIndex);
	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
	{
		FPlatformFileManager::Get().GetPlatformFile().DeleteFile(*FilePath);
		UE_LOG(LogTemp, Log, TEXT("DeleteSave: slot %d deleted"), SlotIndex);
	}
}

// ---- Gap D Execs (UGameInstance is the reliable exec sink in headless -game) ----
void UR3ALN3TGameInstance::RunEnemySoulSequence(float Baseline, const FString& ForkStr)
{
	if (UR3ALN3T_BattleManager* BM = GetSubsystem<UR3ALN3T_BattleManager>())
	{
		BM->RunEnemySoulSequence(Baseline, ForkStr);
	}
}

void UR3ALN3TGameInstance::RunSoulRoundTrip(float PlayerSoulValue, float TrinityValue,
                                            float TyrannyValue, float EternityValue)
{
	if (UR3ALN3T_BattleManager* BM = GetSubsystem<UR3ALN3T_BattleManager>())
	{
		BM->RunSoulRoundTrip(PlayerSoulValue, TrinityValue, TyrannyValue, EternityValue);
	}
}

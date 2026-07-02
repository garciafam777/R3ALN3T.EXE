#include "R3ALN3TGameInstance.h"
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

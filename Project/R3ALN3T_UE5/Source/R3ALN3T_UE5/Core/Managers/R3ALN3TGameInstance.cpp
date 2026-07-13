#include "R3ALN3TGameInstance.h"
#include "../../Gameplay/Battle/R3ALN3T_BattleManager.h" // Gap D: UR3ALN3T_BattleManager (RunEnemySoulSequence / RunSoulRoundTrip / GapBTest)
#include "../../Gameplay/Battle/Cards/ChipDatabase.h"      // Gap E: UChipDatabase::ResolveChipDamage
#include "../../Gameplay/Battle/GrayBoxPlayerPawn.h"        // Gap E: AGrayBoxPlayerPawn (spawn to prove pawn->trigger path)
#include "../../Gameplay/Battle/SanctionEnforcer.h"         // Gap F: USanctionEnforcer runtime verification
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

	// Gap harness auto-run: fired only when -RunGapHarness is on the cmdline.
	// Lets headless -game capture real B/C/D/E play-evidence without a console/player.
	if (FParse::Param(FCommandLine::Get(), TEXT("RunGapHarness")))
	{
		UE_LOG(LogTemp, Log, TEXT("[GAP-HARNESS] auto-run START (cmdline flag)"));
		RunSoulRoundTrip(50.f, 70.f, 30.f, 85.f);   // Gap D: save->mutate->load round-trip
		RunEnemySoulSequence(50.f, TEXT("Fire"));     // Gap C: enemy soul fork sequence
		GapBTest();                                   // Gap B: encounter + element multiplier MATCH
		GapBKillTest();                               // Gap B/E: kill -> IsEncounterCleared
		GapFTest();                                  // Gap F: SanctionEnforcer runtime verification
		UE_LOG(LogTemp, Log, TEXT("[GAP-HARNESS] auto-run DONE"));
	}
}

FString UR3ALN3TGameInstance::GetSavePath(int32 SlotIndex) const
{
	return FPaths::ProjectSavedDir() / TEXT("SaveGames") / FString::Printf(TEXT("slot_%02d.json"), SlotIndex);
}

static TSharedPtr<FJsonObject> RunStateToJson(const FMythosRunState& State)
{
	TSharedPtr<FJsonObject> J = MakeShareable(new FJsonObject());
	J->SetStringField(FStringView(TEXT("OperatorName")), State.OperatorName);
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
	J->SetStringField(FStringView(TEXT("Objective")), State.Objective);
	J->SetStringField(FStringView(TEXT("EndingName")), State.EndingName);
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
		Cj->SetStringField(FStringView(TEXT("NetPID")), C.NetPID.ToString());
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

// ---- Gap E Exec: deterministic battle-encounter proof (headless -game) ----
void UR3ALN3TGameInstance::GapBTest()
{
	UR3ALN3T_BattleManager* BM = GetSubsystem<UR3ALN3T_BattleManager>();
	UChipDatabase* ChipDB = GetSubsystem<UChipDatabase>();
	if (!BM || !ChipDB)
	{
		UE_LOG(LogTemp, Error, TEXT("[GAPB-ENC] BattleManager or ChipDB subsystem unavailable."));
		return;
	}

	// Aqua enemy so a Fire chip (Alpha, power 40) lands strong-against (x2.0) per
	// R3ALN3T's wheel (Fire > Aqua). Proves the strong-against branch of the multiplier.
	FEnemyDef AquaEnemy;
	AquaEnemy.EnemyID = TEXT("GAPB_TEST_AQUA");
	AquaEnemy.DisplayName = FText::FromString(TEXT("Test Aqua Grunt"));
	AquaEnemy.Source = EEnemySource::Virus;
	AquaEnemy.HP = 120;
	AquaEnemy.MaxHP = 120;
	AquaEnemy.Element = EBattleElementType::Aqua;
	AquaEnemy.SpawnCoord = FGridCoord(4, 0);

	BM->BeginEncounter({ AquaEnemy });

	const int32 Col = 4, Row = 0;
	const int32 HP0 = BM->GetEnemyCurrentHP(Col, Row);
	UE_LOG(LogTemp, Log, TEXT("[GAPB-ENC] Placed Aqua enemy @ col %d row %d, HP=%d"), Col, Row, HP0);

	// Resolve the Fire chip (Alpha, power 40) vs Aqua target -> engine returns the multiplier.
	const FName FireChip = TEXT("Alpha");
	const float Expected = ChipDB->ResolveChipDamage(FireChip, EBattleElementType::Aqua);
	const float Mult = Expected / 40.0f;
	UE_LOG(LogTemp, Log, TEXT("[GAPB-DMG] %s (Fire,40) vs Aqua -> multiplier x%.1f, expected dmg=%.0f"),
		*FireChip.ToString(), Mult, Expected);

	BM->PlayChip(FireChip, Col, Row);

	const int32 HP1 = BM->GetEnemyCurrentHP(Col, Row);
	const int32 Dropped = HP0 - HP1;
	const bool bMatch = FMath::IsNearlyEqual(static_cast<float>(Dropped), Expected);
	UE_LOG(LogTemp, Log, TEXT("[GAPB-DMG] HP %d -> %d (dropped %d) | expected %.0f | %s"),
		HP0, HP1, Dropped, Expected, bMatch ? TEXT("MATCH") : TEXT("MISMATCH"));
}

// ---- Gap E Exec: prove the pawn->trigger->BattleManager production path headless ----
void UR3ALN3TGameInstance::GapBSpawnPawn()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("[GAPB-PAWN] No world available to spawn into."));
		return;
	}

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AGrayBoxPlayerPawn* Pawn = World->SpawnActor<AGrayBoxPlayerPawn>(
		AGrayBoxPlayerPawn::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, Params);

	if (Pawn)
	{
		UE_LOG(LogTemp, Log, TEXT("[GAPB-PAWN] Spawned GrayBoxPlayerPawn @ origin. BeginPlay->ForceEncounter fires the production path."));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[GAPB-PAWN] Spawn failed."));
	}
}

// ---- Gap E Exec: prove the KILL + encounter-cleared branch headless ----
void UR3ALN3TGameInstance::GapBKillTest()
{
	UR3ALN3T_BattleManager* BM = GetSubsystem<UR3ALN3T_BattleManager>();
	if (!BM)
	{
		UE_LOG(LogTemp, Error, TEXT("[GAPB-KILL] BattleManager subsystem unavailable."));
		return;
	}

	// Low-HP Aqua enemy so a single Fire chip (Alpha, x2.0 -> 80) drops 40 -> 0.
	FEnemyDef AquaEnemy;
	AquaEnemy.EnemyID = TEXT("GAPB_TEST_KILL");
	AquaEnemy.DisplayName = FText::FromString(TEXT("Test Aqua (low HP)"));
	AquaEnemy.Source = EEnemySource::Virus;
	AquaEnemy.HP = 40;
	AquaEnemy.MaxHP = 40;
	AquaEnemy.Element = EBattleElementType::Aqua;
	AquaEnemy.SpawnCoord = FGridCoord(4, 0);

	BM->BeginEncounter({ AquaEnemy });
	const int32 HP0 = BM->GetEnemyCurrentHP(4, 0);
	UE_LOG(LogTemp, Log, TEXT("[GAPB-KILL] Placed Aqua enemy HP=%d @ col 4"), HP0);

	BM->PlayChip(TEXT("Alpha"), 4, 0); // Fire, x2.0 vs Aqua -> 80 dmg -> dead

	const int32 HP1 = BM->GetEnemyCurrentHP(4, 0);
	const bool bCleared = BM->IsEncounterCleared();
	UE_LOG(LogTemp, Log, TEXT("[GAPB-KILL] HP %d -> %d | IsEncounterCleared=%s"),
		HP0, HP1, bCleared ? TEXT("TRUE") : TEXT("FALSE"));
}

// ---- Gap F Exec: SanctionEnforcer runtime verification (headless -game) ----
// Verifies the REAL engine functions (not a Python mirror): detection-radius boosts,
// fugitive/echo transforms, null-target safety, AddUnique idempotency, PersistTo no-op.
void UR3ALN3TGameInstance::GapFTest()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("[GAPF] No world available."));
		return;
	}

	// Spawn a real actor to serve as the sanction target (proven GrayBoxPlayerPawn path).
	AGrayBoxPlayerPawn* Target = World->SpawnActor<AGrayBoxPlayerPawn>();
	if (!Target)
	{
		UE_LOG(LogTemp, Error, TEXT("[GAPF] Failed to spawn target pawn."));
		return;
	}

	USanctionEnforcer* SE = NewObject<USanctionEnforcer>(this);
	if (!SE)
	{
		UE_LOG(LogTemp, Error, TEXT("[GAPF] Failed to create SanctionEnforcer."));
		return;
	}

	// (1) Null-target safety: ApplySanction(nullptr) must NOT crash.
	SE->ApplySanction(ESanctionType::Marked, nullptr, TEXT("null-target-safety"));
	UE_LOG(LogTemp, Log, TEXT("[GAPF-NULL] ApplySanction(nullptr) returned without crash | PASS"));

	// (2) Detection-radius boosts (real code: Marked +500, Wanted +1500, Fugitive +3000).
	SE->ApplySanction(ESanctionType::Marked, Target, TEXT("visual-tag"));
	const float BoostMarked = SE->GetDetectionRadiusBoost(Target);
	UE_LOG(LogTemp, Log, TEXT("[GAPF-BOOST] Marked boost=%.0f (expected 500) | %s"),
		BoostMarked, FMath::IsNearlyEqual(BoostMarked, 500.f) ? TEXT("MATCH") : TEXT("MISMATCH"));

	SE->ApplySanction(ESanctionType::Wanted, Target, TEXT("bounty"));
	const float BoostWanted = SE->GetDetectionRadiusBoost(Target);
	UE_LOG(LogTemp, Log, TEXT("[GAPF-BOOST] Marked+Wanted boost=%.0f (expected 2000) | %s"),
		BoostWanted, FMath::IsNearlyEqual(BoostWanted, 2000.f) ? TEXT("MATCH") : TEXT("MISMATCH"));

	SE->ApplySanction(ESanctionType::Fugitive, Target, TEXT("manhunt"));
	const float BoostFugitive = SE->GetDetectionRadiusBoost(Target);
	UE_LOG(LogTemp, Log, TEXT("[GAPF-BOOST] Marked+Wanted+Fugitive boost=%.0f (expected 5000) | %s"),
		BoostFugitive, FMath::IsNearlyEqual(BoostFugitive, 5000.f) ? TEXT("MATCH") : TEXT("MISMATCH"));

	// (3) Fugitive / Echo transform gates.
	const bool bFugitive = SE->IsFugitive(Target);
	UE_LOG(LogTemp, Log, TEXT("[GAPF-ISFUG] IsFugitive=%s (expected TRUE) | %s"),
		bFugitive ? TEXT("TRUE") : TEXT("FALSE"), bFugitive ? TEXT("MATCH") : TEXT("MISMATCH"));

	const bool bEchoBefore = SE->ShouldTransformToEcho(Target);
	SE->ApplySanction(ESanctionType::Echoed, Target, TEXT("character-loss"));
	const bool bEchoAfter = SE->ShouldTransformToEcho(Target);
	UE_LOG(LogTemp, Log, TEXT("[GAPF-ECHO] Before=%s After=%s (expected FALSE->TRUE) | %s"),
		bEchoBefore ? TEXT("TRUE") : TEXT("FALSE"), bEchoAfter ? TEXT("TRUE") : TEXT("FALSE"),
		(!bEchoBefore && bEchoAfter) ? TEXT("MATCH") : TEXT("MISMATCH"));

	// (4) AddUnique idempotency: re-applying same sanction must not duplicate.
	SE->ApplySanction(ESanctionType::Marked, Target, TEXT("reapply"));
	int32 MarkedCount = 0;
	if (const TArray<ESanctionType>* S = SE->GetActiveSanctionsForDebug(Target))
	{
		for (ESanctionType T : *S) if (T == ESanctionType::Marked) MarkedCount++;
	}
	UE_LOG(LogTemp, Log, TEXT("[GAPF-UNIQ] Marked reapply count=%d (expected 1) | %s"),
		MarkedCount, MarkedCount == 1 ? TEXT("MATCH") : TEXT("MISMATCH"));

	// (5) PersistTo is a deliberate no-op (sanctions are non-serializable AActor* state).
	SE->PersistTo(nullptr); // must not crash; intentionally writes nothing
	UE_LOG(LogTemp, Log, TEXT("[GAPF-PERSIST] PersistTo(nullptr) no-op, no crash | PASS"));

	UE_LOG(LogTemp, Log, TEXT("[GAPF] SanctionEnforcer runtime verification complete."));
}

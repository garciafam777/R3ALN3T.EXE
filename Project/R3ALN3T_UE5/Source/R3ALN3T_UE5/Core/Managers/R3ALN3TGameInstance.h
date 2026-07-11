// Master persistent state management — UGameInstance subclass that survives map transitions.
// Owns the save/load interface, narrative manager, and global game config.
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "../../Services/BackendClient.h"
#include "../Types/MythosGameTypes.h"
#include "../Types/SoulState.h"                  // Gap D: FSoulState
#include "../../Gameplay/Characters/R3ALN3T_NetPStructures.h" // Gap D: FCompanionSoul
#include "R3ALN3TGameInstance.generated.h"

class UNarrativeManager;

USTRUCT(BlueprintType)
struct FPersistentRunData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FMythosRunState RunState;

	UPROPERTY(BlueprintReadWrite)
	TArray<FString> Inventory;

	UPROPERTY(BlueprintReadWrite)
	int32 ActiveStoryNodeIndex = 0;

	// Gap D: persistent souls. Player soul + the 3 companion souls (Trinity/Tyranny/
	// Eternity) round-trip through SaveGame/LoadGame. Seeded to 50 in Init().
	UPROPERTY(BlueprintReadWrite)
	FSoulState PlayerSoul;

	UPROPERTY(BlueprintReadWrite)
	TArray<FCompanionSoul> NetPSouls;
};

UCLASS()
class R3ALN3T_UE5_API UR3ALN3TGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UR3ALN3TGameInstance();

	virtual void Init() override;

	// Gap D Execs (console): routed through UGameInstance because it is the one exec
	// sink guaranteed to exist in a headless -game run (the test map uses AGameModeBase,
	// so the PlayerController/Pawn exec sinks are never spawned). Forwards to the
	// BattleManager so the logic lives in one place.
	UFUNCTION(Exec)
	void RunEnemySoulSequence(float Baseline = 50.f, const FString& ForkStr = TEXT("Spare"));

	UFUNCTION(Exec)
	void RunSoulRoundTrip(float PlayerSoulValue = 50.f, float TrinityValue = 50.f,
	                      float TyrannyValue = 50.f, float EternityValue = 50.f);

	// Gap E Exec (console): headless proof of the battle-encounter vertical slice.
	// Places a Fire enemy on the grid (col 4), resolves an Aqua chip (Delta) against it,
	// and logs the element multiplier + HP drop so the encounter path is verifiable from
	// a -game launch. Same exec-sink discipline as Gap D (UGameInstance is always present).
	// e.g. `GapBTest`
	UFUNCTION(Exec)
	void GapBTest();

	// Gap E Exec: spawns AGrayBoxPlayerPawn into the world. Its BeginPlay (bForceEncounterOnStart)
	// fires the REAL pawn->EncounterTriggerComponent->BattleManager production path, logging
	// [GAPB-PIE]. Distinct from GapBTest (which calls BeginEncounter directly) — this proves
	// the pawn wiring itself, headless. e.g. `GapBSpawnPawn`
	UFUNCTION(Exec)
	void GapBSpawnPawn();

	// Gap E Exec: proves the KILL + encounter-cleared branch. Places a low-HP Aqua enemy
	// (HP 40) and lands a Fire chip (Alpha, x2.0 -> 80) to drop it to 0, then logs
	// IsEncounterCleared(). e.g. `GapBKillTest`
	UFUNCTION(Exec)
	void GapBKillTest();

	// --- Save/Load ---
	UFUNCTION(BlueprintCallable, Category = "Save")
	void SaveGame(int32 SlotIndex);

	UFUNCTION(BlueprintCallable, Category = "Save")
	bool LoadGame(int32 SlotIndex);

	UFUNCTION(BlueprintCallable, Category = "Save")
	TArray<FPersistentRunData> GetAllSavePreviews() const;

	UFUNCTION(BlueprintCallable, Category = "Save")
	bool HasSaveData(int32 SlotIndex) const;

	UFUNCTION(BlueprintCallable, Category = "Save")
	void DeleteSave(int32 SlotIndex);

	// --- Settings ---
	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	float MasterVolume = 1.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	float SFXVolume = 1.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	bool bFullscreen = true;

	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	int32 ResolutionX = 1920;

	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	int32 ResolutionY = 1080;

	// --- Narrative Manager ---
	UPROPERTY(BlueprintReadOnly, Category = "Narrative")
	UNarrativeManager* NarrativeManager = nullptr;

	// --- Backend Bridge ---
	UPROPERTY(BlueprintReadOnly, Category = "Backend")
	ABackendClient* BackendClient = nullptr;

	// --- Active Run ---
	UPROPERTY(BlueprintReadWrite, Category = "Run")
	FPersistentRunData CurrentRun;

protected:
	FString GetSavePath(int32 SlotIndex) const;
	static constexpr int32 MaxSaveSlots = 10;
};

// R3ALSaveGame.h — persistent save (Nyx/engine-dev v2, Trinity Matrix canon)
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "../../Core/Types/TrinityMatrixTypes.h"
#include "../../Core/Types/SoulState.h"   // Area-3: ESoulAuraBand for player soul band
#include "R3ALSaveGame.generated.h"

// Phase1-A3: Rotterdam reward block. Mirrors the battle-time FBattleResult
// (battle result is defined in R3ALN3T_BattleManager.h; we keep a decoupled
// reward record here so the save schema doesn't pull in the battle manager).
USTRUCT(BlueprintType)
struct FR3ALN3TRewardRecord
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reward")
	bool bPlayerWon = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reward")
	int32 ZEarned = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reward")
	TArray<FName> ChipsEarned;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reward")
	int32 XP_Earned = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reward")
	int32 EnemiesDefeated = 0;

	// Origin tag (e.g. "Rotterdam", "Location02") so rewards are attributable.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reward")
	FString LocationTag;

	// Epoch seconds when the encounter resolved (sorting / dedup key).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reward")
	int64 TimestampUTC = 0;
};

// Wrapper so a TArray<FString> can be used as a reflected TMap value.
USTRUCT(BlueprintType)
struct FStringArray
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	TArray<FString> Items;
};

UCLASS()
class R3ALN3T_UE5_API UR3ALSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	// 3 NetP constructs (Trinity/Tyranny/Eternity); unused slots stay default.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	TMap<ENetPConstruct, FR3ALN3TNetPStatus> NetPs;

	// Collected chip folders keyed by construct.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	TMap<ENetPConstruct, FStringArray> ChipFolders;

	// Career unlocks (career IDs from the 252+ path table).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	TArray<FString> UnlockedCareers;

	// Faction reputation (-100..100 per faction).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	TMap<EFaction, int32> FactionRep;

	// Soul State per construct (-1 Infernal .. +1 Celestial).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	TMap<ENetPConstruct, ESoulState> SoulState;

	// Area-3 fix: the player's own soul band (0-100 mapped to ESoulAuraBand), persisted
	// on battle resolution so grid/faction/soul edits survive a restart.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save|Soul")
	ESoulAuraBand PlayerSoulBand = ESoulAuraBand::Cracked;

	// Chapter 5.3: player's overworld location at the moment an encounter triggered, so
	// the overworld can be re-entered at the same spot after battle resolves.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save|World")
	FVector LastWorldLocation = FVector::ZeroVector;

	// Story flags (act completion, secret-chapter discovery).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	TSet<FString> StoryFlags;

	// Highest Greek tier achieved (for Trinity unlock check).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	EGreekTier HighestRank = EGreekTier::OmicronPSI;

	// Phase1-A3: Rotterdam reward block (append-only history of resolved encounters).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save|Rewards")
	TArray<FR3ALN3TRewardRecord> RewardHistory;

	// Phase1-A3: persist a finished encounter's reward block.
	UFUNCTION(BlueprintCallable, Category = "Save|Rewards")
	void PersistReward(const FR3ALN3TRewardRecord& Reward);

	// Phase1-A3: canonical slot + load/create/save helpers (round-trip survives restart).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save|Mock")
	FString PlayerNotes;   // Area-2: raw player-state JSON stash used by the local mock backend

	static const FString SaveSlotName;
	static UR3ALSaveGame* LoadOrCreate(UObject* Outer);
	static bool Save(UObject* Outer, UR3ALSaveGame* Save);
};

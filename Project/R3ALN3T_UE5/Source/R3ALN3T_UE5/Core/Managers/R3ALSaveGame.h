// R3ALSaveGame.h — persistent save (Nyx/engine-dev v2, Trinity Matrix canon)
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "../../Core/Types/TrinityMatrixTypes.h"
#include "R3ALSaveGame.generated.h"

// Wrapper so a TArray<FString> can be used as a reflected TMap value.
USTRUCT(BlueprintType)
struct FStringArray
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Save")
    TArray<FString> Items;
};

UCLASS()
class R3ALN3T_UE5_API UR3ALSaveGame : public USaveGame
{
    GENERATED_BODY()
public:
    // 3 NetP constructs (Trinity/Tyranny/Eternity); unused slots stay default.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Save")
    TMap<ENetPConstruct, FR3ALN3TNetPStatus> NetPs;

    // Collected chip folders keyed by construct.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Save")
    TMap<ENetPConstruct, FStringArray> ChipFolders;

    // Career unlocks (career IDs from the 252+ path table).
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Save")
    TArray<FString> UnlockedCareers;

    // Faction reputation (-100..100 per faction).
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Save")
    TMap<EFaction, int32> FactionRep;

    // Soul State per construct (-1 Infernal .. +1 Celestial).
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Save")
    TMap<ENetPConstruct, ESoulState> SoulState;

    // Story flags (act completion, secret-chapter discovery).
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Save")
    TSet<FString> StoryFlags;

    // Highest Greek tier achieved (for Trinity unlock check).
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Save")
    EGreekTier HighestRank = EGreekTier::OmicronPSI;
};

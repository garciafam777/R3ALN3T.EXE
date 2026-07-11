// R3ALSaveGame.h — persistent save (Nyx/engine-dev, compile-ready)
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Core/Types/SoulBattleTypes.h"
#include "R3ALSaveGame.generated.h"

UCLASS()
class R3ALN3T_UE5_API UR3ALSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	// NetP collection (player roster + OMEGA status extensions)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	TArray<FR3ALN3TNetPStatus> NetPCollection;

	// Chip folder (owned chip ids + memory cost)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	TArray<FString> ChipFolder;

	// Career unlocks (tier reached per element)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	TMap<EBattleElementType, EOmegaCareerTier> CareerUnlocks;

	// Story flags (narrative nodes reached)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	TSet<FString> StoryFlags;

	// Active sanctions on the player (persist across saves)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	TArray<ESanctionType> ActiveSanctions;

	// Player's OMEGA supremacy (set on usurp)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	ESupremacyTier PlayerSupremacy = ESupremacyTier::NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	EBattleElementType ClaimedDomain = EBattleElementType::None;
};

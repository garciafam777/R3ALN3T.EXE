// R3ALSaveGame.cpp — persistent save (Nyx/engine-dev v2, Phase1-A3 reward binding)
#include "R3ALSaveGame.h"
#include "Kismet/GameplayStatics.h"

// Serialization handled by UE native UPROPERTY reflection:
// TMap/TArray/TSet of UENUM/USTRUCT types round-trip automatically on SaveGame write.
// No custom serializer required.

const FString UR3ALSaveGame::SaveSlotName = TEXT("R3ALN3T_Save_01");
const int32 SaveUserIndex = 0;

void UR3ALSaveGame::PersistReward(const FR3ALN3TRewardRecord& Reward)
{
	RewardHistory.Add(Reward);
}

UR3ALSaveGame* UR3ALSaveGame::LoadOrCreate(UObject* Outer)
{
	if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, SaveUserIndex))
	{
		USaveGame* Existing = UGameplayStatics::LoadGameFromSlot(SaveSlotName, SaveUserIndex);
		if (UR3ALSaveGame* AsSave = Cast<UR3ALSaveGame>(Existing))
		{
			return AsSave;
		}
	}
	// No save yet (or corrupt) — create a fresh one with the runtime Outer.
	UObject* UseOuter = Outer ? Outer : static_cast<UObject*>(GetTransientPackage());
	return NewObject<UR3ALSaveGame>(UseOuter);
}

bool UR3ALSaveGame::Save(UObject* Outer, UR3ALSaveGame* Save)
{
	if (!Save) return false;
	return UGameplayStatics::SaveGameToSlot(Save, SaveSlotName, SaveUserIndex);
}

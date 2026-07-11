// R3ALSaveGame.cpp — persistent save (Nyx/engine-dev)
#include "R3ALSaveGame.h"

// Serialization is handled by UE's native UPROPERTY reflection (TArray/TMap/TSet of
// USTRUCT/UENUM types round-trip through USaveGame::Serialize automatically). No custom
// archive code needed — sanctions, NetP status, career unlocks all persist by default.
// Caller uses UGameplayStatics::SaveGameToSlot / LoadGameFromSlot with this class.

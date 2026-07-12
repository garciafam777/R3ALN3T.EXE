// R3ALSaveGame.cpp — persistent save (Nyx/engine-dev v2)
#include "R3ALSaveGame.h"

// Serialization handled by UE native UPROPERTY reflection:
// TMap/TArray/TSet of UENUM/USTRUCT types round-trip automatically on SaveGame write.
// No custom serializer required.

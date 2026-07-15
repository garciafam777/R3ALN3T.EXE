// FactionTypes.h — data-driven Construct Roster registry (Trinity / Tyranny / Eternity slice).
//
// NOTE on canon: Trinity/Tyranny/Eternity are ENetPConstruct (not EFaction — the 26-value
// EFaction enum is alignment-lean, not which NetP you field). The roster is keyed by
// ENetPConstruct so adding the 23 design-vocab factions later is purely a DataTable row,
// no C++ change. Output is FR3ALN3TNetPStatus (the real NetP carrier) — NOT a fictional
// FNetPSpawnData/NetPClass. Mirrors the FrameByElement data-driven pattern.
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "../../Core/Types/TrinityMatrixTypes.h" // ENetPConstruct, FR3ALN3TNetPStatus, EElement, EFaction
#include "FactionTypes.generated.h"

// A weighted unit template inside a construct's roster.
// Weights a partial FR3ALN3TNetPStatus (identity + stat seeds); full stat roll is done by
// UNetPRandomizer so the ZETA ceiling stays the single source of truth for tiers.
USTRUCT(BlueprintType)
struct FNetPRosterUnit : public FTableRowBase
{
    GENERATED_BODY()

    // Identity this unit seeds onto the spawned NetP.
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Roster")
    ENetPConstruct Construct = ENetPConstruct::Trinity;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Roster")
    EElement Element = EElement::None; // None => let randomizer pick a canon element

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Roster")
    EFaction FactionLean = EFaction::None;

    // Relative pick weight in the roster (>=1). Simple weighted roll, PoC-grade.
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Roster")
    float SpawnWeight = 1.0f;
};

// One construct's roster row. RowName in the DataTable == ENetPConstruct name
// ("Trinity", "Tyranny", "Eternity").
USTRUCT(BlueprintType)
struct FConstructRosterRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Roster")
    ENetPConstruct Construct = ENetPConstruct::Trinity;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Roster")
    TArray<FNetPRosterUnit> Units;
};

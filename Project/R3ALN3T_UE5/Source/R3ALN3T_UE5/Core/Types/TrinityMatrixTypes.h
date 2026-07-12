// TrinityMatrixTypes.h — R3ALN3T.EXE canonical type system (Nyx/engine-dev v2)
// Source of truth: Updated .md files/05 (Battle), /08 (Trinity Progression), Trinity Matrix.
// 3 axes: [TIER Greek ladder] x [TYPE Code-Philosophy] x [ELEMENT 18].
#pragma once
#include "CoreMinimal.h"
#include "TrinityMatrixTypes.generated.h"

// Axis 3: 18 Elements (paired; uniform multipliers per Book 5).
UENUM(BlueprintType)
enum class EElement : uint8
{
    None      UMETA(DisplayName="None"),
    Fire      UMETA(DisplayName="Fire"),
    Aqua      UMETA(DisplayName="Aqua"),
    Elec      UMETA(DisplayName="Elec"),
    Wood      UMETA(DisplayName="Wood"),
    Wind      UMETA(DisplayName="Wind"),
    Earth     UMETA(DisplayName="Earth"),
    Light     UMETA(DisplayName="Light"),
    Dark      UMETA(DisplayName="Dark"),
    Null      UMETA(DisplayName="Null"),
    Glitch    UMETA(DisplayName="Glitch"),
    Plasma    UMETA(DisplayName="Plasma"),
    Crystal   UMETA(DisplayName="Crystal"),
    Time      UMETA(DisplayName="Time"),
    Gravity   UMETA(DisplayName="Gravity"),
    Sound     UMETA(DisplayName="Sound"),
    Metal     UMETA(DisplayName="Metal"),
    Poison    UMETA(DisplayName="Poison"),
    Nature    UMETA(DisplayName="Nature")
};
inline constexpr int32 EElement_COUNT = 19; // includes None

// Axis 1: Greek Capacity Ladder (Omicron-PSI lowest -> Omega highest).
UENUM(BlueprintType)
enum class EGreekTier : uint8
{
    OmicronPSI UMETA(DisplayName="Omicron-PSI"), // starting tier
    Zeta       UMETA(DisplayName="Zeta"),
    Epsilon    UMETA(DisplayName="Epsilon"),
    Delta      UMETA(DisplayName="Delta"),
    Gamma      UMETA(DisplayName="Gamma"),
    Beta       UMETA(DisplayName="Beta"),
    Alpha      UMETA(DisplayName="Alpha"),
    Omega      UMETA(DisplayName="Omega") // Trinity ceiling
};

// Axis 2: Core Code-Philosophy (Type).
UENUM(BlueprintType)
enum class ECodePhilosophy : uint8
{
    Mechanical UMETA(DisplayName="Mechanical"),
    Viral      UMETA(DisplayName="Viral"),
    Angelic    UMETA(DisplayName="Angelic"),
    Demonic    UMETA(DisplayName="Demonic")
};

// 6 Factions (alignment leans from careers).
UENUM(BlueprintType)
enum class EFaction : uint8
{
    None,
    CelestialOrder,
    AegisConcord,
    N3TDominion,
    FreeGridCollective,
    UndernetSyndicate,
    AbyssalCovenant
};

// The 3 NetP Constructs (Trinity unlocks at Omega rank).
UENUM(BlueprintType)
enum class ENetPConstruct : uint8
{
    Trinity UMETA(DisplayName="Trinity"),   // Primary (base game)
    Tyranny UMETA(DisplayName="Tyranny"),   // Secondary (NG+)
    Eternity UMETA(DisplayName="Eternity")  // Tertiary (Trinity unlock)
};

// Soul State scale: 0 Infernal lean .. 2 Celestial lean (uint8 required for BlueprintType).
UENUM(BlueprintType)
enum class ESoulState : uint8
{
    Infernal  = 0,
    Neutral   = 1,
    Celestial = 2
};

// 6 core NetP stats (Book 5).
USTRUCT(BlueprintType)
struct FR3ALN3TNetPStatus
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 HP = 60;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 ATK = 12;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) float RAPID = 0.1f; // crit/multi-hit chance
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 CHARGE = 10;  // turn initiative
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 DEF = 5;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 SPD = 3;
    // Trinity Matrix placement
    UPROPERTY(EditAnywhere, BlueprintReadWrite) EGreekTier Tier = EGreekTier::OmicronPSI;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) ECodePhilosophy Philosophy = ECodePhilosophy::Mechanical;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) EElement Element = EElement::None;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) EFaction FactionLean = EFaction::None;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) ESoulState Soul = ESoulState::Neutral;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) ENetPConstruct Construct = ENetPConstruct::Trinity;
};

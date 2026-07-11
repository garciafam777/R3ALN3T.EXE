// NetPTypes.h - OMEGA supremacy enums (PROPOSAL, Nyx/DevOps)
// REVIEW-ONLY: not committed to Source/ until approved.md. Grounded in
// verified 7-wheel (BattleGridTypes.h:19) + 16-tier enum.
#pragma once
#include "CoreMinimal.h"
#include "NetPTypes.generated.h"

UENUM(BlueprintType)
enum class EElement : uint8
{
    Fire    UMETA(DisplayName = "Fire"),
    Aqua    UMETA(DisplayName = "Aqua"),
    Elec    UMETA(DisplayName = "Elec"),
    Wood    UMETA(DisplayName = "Wood"),
    Wind    UMETA(DisplayName = "Wind"),
    Holy    UMETA(DisplayName = "Holy"),
    Void    UMETA(DisplayName = "Void")
};

UENUM(BlueprintType)
enum class ECareerTier : uint8
{
    OMEGA = 0, ALPHA, BETA, GAMMA, DELTA, EPSILON,
    ZETA, ETA, THETA, IOTA, KAPPA, LAMBDA,
    MU, NU, XI, OMICRON
};

UENUM(BlueprintType)
enum class ESupremacyTier : uint8
{
    NONE      UMETA(DisplayName = "None"),
    ELEMENTAL UMETA(DisplayName = "Elemental"),
    PRIME     UMETA(DisplayName = "Prime"),
    EXILED    UMETA(DisplayName = "Exiled")
};

UENUM(BlueprintType)
enum class ECovenantState : uint8
{
    DORMANT   UMETA(DisplayName = "Dormant"),
    ACTIVE    UMETA(DisplayName = "Active"),
    ALIGNED   UMETA(DisplayName = "Aligned"),
    HOSTILE   UMETA(DisplayName = "Hostile"),
    USURPED   UMETA(DisplayName = "Usurped")
};

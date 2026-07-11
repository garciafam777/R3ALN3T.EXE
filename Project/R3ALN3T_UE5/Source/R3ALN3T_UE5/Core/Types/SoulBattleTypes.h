// SoulBattleTypes.h — OMEGA Overlord supremacy types (Nyx/engine-dev, compile-ready)
// Uses engine EBattleElementType (BattleGridTypes.h:17) for the canonical 7-wheel.
#pragma once
#include "CoreMinimal.h"
#include "Core/Types/BattleGridTypes.h"   // EBattleElementType (None,Fire,Aqua,Elec,Wood,Wind,Holy,Void)
#include "SoulBattleTypes.generated.h"

// OMEGA supremacy tier (new — not in engine yet)
UENUM(BlueprintType)
enum class ESupremacyTier : uint8
{
	NONE      UMETA(DisplayName = "None"),
	ELEMENTAL UMETA(DisplayName = "Elemental"),
	PRIME     UMETA(DisplayName = "Prime"),
	EXILED    UMETA(DisplayName = "Exiled")
};

// Covenant relationship state between player and an OMEGA
UENUM(BlueprintType)
enum class ECovenantState : uint8
{
	DORMANT   UMETA(DisplayName = "Dormant"),
	ACTIVE    UMETA(DisplayName = "Active"),
	ALIGNED   UMETA(DisplayName = "Aligned"),
	HOSTILE   UMETA(DisplayName = "Hostile"),
	USURPED   UMETA(DisplayName = "Usurped")
};

// OMEGA career progression (OMEGA = apex, OMICRON = starter). New enum.
UENUM(BlueprintType)
enum class EOmegaCareerTier : uint8
{
	OMICRON = 0, ALPHA, BETA, GAMMA, DELTA, EPSILON,
	ZETA, ETA, THETA, IOTA, KAPPA, LAMBDA,
	MU, NU, XI, OMEGA
};

// The 12 sanction types from the lore draft
UENUM(BlueprintType)
enum class ESanctionType : uint8
{
	MARKED,        // visual tag; hostile AI detection boost
	WANTED,        // bounty; AI perception radius boost
	OUTLAW,        // barred from safe zones
	BANISHED,      // removed from faction
	CURSED,        // stat debuff
	BRANDED,       // permanent mark
	SILENCED,      // cannot use non-OMEGA abilities
	SHACKLED,      // movement lock
	FUGITIVE,      // GAMMA NPCs hunt + teleport on same map
	ECHOED,        // transformation to AEchoNPC (character loss)
	NULLIFIED,     // powers suppressed
	ERASED         // full wipe (worst case)
};

USTRUCT(BlueprintType)
struct FR3ALN3TNetPStatus
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite) FString NetPId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FString DisplayName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EBattleElementType Element = EBattleElementType::None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EOmegaCareerTier CareerTier = EOmegaCareerTier::OMICRON;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 CSI = 100; // 0-100
	UPROPERTY(EditAnywhere, BlueprintReadWrite) ESupremacyTier SupremacyTier = ESupremacyTier::NONE;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EBattleElementType DomainElement = EBattleElementType::None; // OMEGA ELEMENTAL claims this
	UPROPERTY(EditAnywhere, BlueprintReadWrite) ECovenantState CovenantState = ECovenantState::DORMANT;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FString FlavorText;
};

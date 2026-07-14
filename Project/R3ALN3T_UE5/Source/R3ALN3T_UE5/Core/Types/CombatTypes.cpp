// CombatTypes.cpp
#include "CombatTypes.h"
#include "Kismet/KismetMathLibrary.h"
#include "TrinityMatrixTypes.h" // EElement (G10 canon-21 bridge)
// Full FVirusDef definition (MakeEnemyDefFromVirus reads its fields). Including the
// manager header here is safe: CombatTypes.h no longer includes it, so no .h cycle.
#include "../../Gameplay/Battle/R3ALN3T_BattleManager.h"

// ----------------------------------------------------------------------------
// Virus -> Enemy (drop-in; preserves existing FVirusDef balance exactly)
// ----------------------------------------------------------------------------
FEnemyDef MakeEnemyDefFromVirus(const FVirusDef& V)
{
	FEnemyDef E;
	E.EnemyID      = V.VirusID;
	E.DisplayName  = V.DisplayName;
	E.Source       = EEnemySource::Virus;
	E.HomeDimension = ER3ALN3TLayer::Reality; // legacy viruses are realm-native
	E.SpawnCoord   = FGridCoord(4, 1);
	E.HP = E.MaxHP = V.HP;
	E.Attack       = V.Attack;
	E.Shield       = V.Shield;
	E.Element      = V.Element;                 // carry the virus's authored element (default None)
	E.ZReward      = V.ZReward;
	E.DropRate     = V.DropRate;
	E.ChipDrops    = V.ChipDrops;
	return E;
}

// ----------------------------------------------------------------------------
// NetP -> Enemy  (THE stat-scaling surface Gap B exists to review)
// ----------------------------------------------------------------------------
// Archetype -> combat element + shield. Mirrors the NetP's narrative role:
//   Vanguard      -> Fire,  +0 shield  (frontal aggression)
//   LogicGate     -> None,  +0 shield  (neutral arbiter)
//   Infiltrator   -> Elec,  +0 shield  (fast, exposed)
//   SentientNode  -> Holy,  +3 shield  (fortified core)
//   Wraith        -> Void,  +5 shield  (phase-resistant)
static EBattleElementType ArchetypeElement(ENetPArchetype A)
{
	switch (A)
	{
		case ENetPArchetype::Vanguard:     return EBattleElementType::Fire;
		case ENetPArchetype::LogicGate:    return EBattleElementType::None;
		case ENetPArchetype::Infiltrator:  return EBattleElementType::Elec;
		case ENetPArchetype::SentientNode: return EBattleElementType::Holy;
		case ENetPArchetype::Wraith:       return EBattleElementType::Void;
	}
	return EBattleElementType::None;
}

static int32 ArchetypeShield(ENetPArchetype A)
{
	switch (A)
	{
		case ENetPArchetype::SentientNode: return 3;
		case ENetPArchetype::Wraith:       return 5;
		default:                           return 0;
	}
}

FEnemyDef MakeEnemyDefFromNetP(const FR3ALN3TNetPProfileRow& N)
{
	FEnemyDef E;
	E.EnemyID       = N.NetPID;
	E.DisplayName   = N.DisplayName;
	E.Source        = EEnemySource::NetP;
	E.Archetype     = N.Archetype;
	E.HomeDimension = N.HomeDimension;          // usually Cyberspace
	E.SpawnCoord    = FGridCoord(4, 1);         // enemy side of 8x4

	// HP: CoreStabilityIndex is the "full" value (100). Processing tier adds pressure
	// but a fresh NetP (BaseProcessingLevel=1) must stay killable early. Bounded so a
	// high-tier node isn't an unkillable wall.
	//   Tier 1: ~45 HP.   Tier 5: ~105 HP.   Monotonic, bounded [20,400].
	const int32 Tier = FMath::Max(1, N.BaseProcessingLevel);
	E.MaxHP = E.HP = FMath::Clamp(
		FMath::RoundToInt(N.CoreStabilityIndex * (0.3f + 0.15f * Tier)), 20, 400);

	// Attack: scales with processing level, floored so it always threatens.
	E.Attack = 4 + Tier * 2;                    // Tier1=6 ... Tier5=14

	// Shield from archetype.
	E.Shield = ArchetypeShield(N.Archetype);

	// Element from archetype (see table above).
	E.Element = ArchetypeElement(N.Archetype);

	// ZReward from throughput (economy link: faster nodes pay more).
	E.ZReward = FMath::RoundToInt(N.BaseThroughputSpeed / 10.0f); // 300 -> 30

	E.DropRate = 0.25f;
	// ChipDrops must be authored on the NetP row (added per Gap B spec §6);
	// left empty here if the row omits them.
	return E;
}

// ----------------------------------------------------------------------------
// Element unification: EMythosElement is RUN-FLAVOR ONLY.
// Run pick (Volt/Aqua/...) maps onto the battle-canonical EBattleElementType.
// After this, NO combat code ever compares EMythosElement.
// ----------------------------------------------------------------------------
EBattleElementType ToBattleElement(EMythosElement E)
{
	switch (E)
	{
		case EMythosElement::Volt:  return EBattleElementType::Elec;
		case EMythosElement::Aqua:  return EBattleElementType::Aqua;
		case EMythosElement::Terra: return EBattleElementType::Wood;
		case EMythosElement::Shade: return EBattleElementType::Void;
		case EMythosElement::Flare: return EBattleElementType::Fire;
		case EMythosElement::Signal:return EBattleElementType::None;
	}
	return EBattleElementType::None;
}

// ----------------------------------------------------------------------------
// Element interaction wheel (single source of truth for TPA multipliers).
// Both operands are EBattleElementType -> no type-pun, no silent mismatch.
// Wheel (strong -> weak): Fire>Aqua, Aqua>Elec, Elec>Wood, Wood>Wind,
//                          Wind>Holy, Holy>Void, Void>Fire  (loops, 7 steps).
// ----------------------------------------------------------------------------
namespace
{
	// index into the canonical ordered wheel (must match EBattleElementType order minus None).
	int32 WheelIndex(EBattleElementType E)
	{
		switch (E)
		{
			case EBattleElementType::Fire:  return 0;
			case EBattleElementType::Aqua:  return 1;
			case EBattleElementType::Elec:  return 2;
			case EBattleElementType::Wood:  return 3;
			case EBattleElementType::Wind:  return 4;
			case EBattleElementType::Holy:  return 5;
			case EBattleElementType::Void:  return 6;
			default:                        return -1; // None
		}
	}
}

float EvaluateElementMultiplier(
	EBattleElementType ChipElement,
	EBattleElementType TargetElement,
	EBattleElementType PanelElement)
{
	// None element is neutral everywhere.
	if (ChipElement == EBattleElementType::None) return 1.0f;

	float Mult = 1.0f;

	// Same element (chip == target): bonus.
	if (ChipElement == TargetElement) Mult = FMath::Max(Mult, 1.5f);

	// Panel buff (chip element matches the tile the target stands on).
	if (PanelElement != EBattleElementType::None && ChipElement == PanelElement)
		Mult = FMath::Max(Mult, 1.25f);

	// Wheel strong/weak.
	const int32 Ci = WheelIndex(ChipElement);
	const int32 Ti = WheelIndex(TargetElement);
	if (Ci >= 0 && Ti >= 0)
	{
		const int32 Steps = (Ti - Ci + 7) % 7; // forward distance on the wheel
		if (Steps == 1)       Mult = FMath::Max(Mult, 2.0f); // chip strong vs target
		else if (Steps == 6)  Mult = FMath::Min(Mult, 0.5f); // chip weak  vs target
	}

	return Mult;
}

// G10 (element unification): 7-wheel combat enum <-> canon-21 EElement bridge.
// Combat structs carry EBattleElementType (7-wheel subset); the canon matrix
// (UElementWheelCalculator::ElementMultiplier) consumes EElement (21). Map the
// 7-wheel values into canon-21. Holy has no canon equivalent -> Light (closest).
EElement ToEElement(EBattleElementType Battle)
{
	switch (Battle)
	{
		case EBattleElementType::None:  return EElement::None;
		case EBattleElementType::Fire:  return EElement::Fire;
		case EBattleElementType::Aqua:  return EElement::Aqua;
		case EBattleElementType::Elec:  return EElement::Elec;
		case EBattleElementType::Wood:  return EElement::Wood;
		case EBattleElementType::Wind:  return EElement::Wind;
		case EBattleElementType::Holy:  return EElement::Light; // no canon Holy -> Light
		case EBattleElementType::Void:  return EElement::Void;
		default:                        return EElement::None;
	}
}

EBattleElementType ToBattleElement(EElement Canon)
{
	switch (Canon)
	{
		case EElement::Fire:  return EBattleElementType::Fire;
		case EElement::Aqua:  return EBattleElementType::Aqua;
		case EElement::Elec:  return EBattleElementType::Elec;
		case EElement::Wood:  return EBattleElementType::Wood;
		case EElement::Wind:  return EBattleElementType::Wind;
		case EElement::Light: return EBattleElementType::Holy; // Light -> Holy for display
		case EElement::Void:  return EBattleElementType::Void;
		default:              return EBattleElementType::None;
	}
}

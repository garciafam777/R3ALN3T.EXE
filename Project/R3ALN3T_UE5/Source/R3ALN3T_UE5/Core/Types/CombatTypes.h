// CombatTypes.h
// Unified combat types for the MMBN-style battle path (Gap B wiring).
//
// SCOPE NOTE: this module deliberately builds on the MMBN chip-folder path
// (FBattleChip + EChipCode Greek codes + ChipFolderComponent + BattleStateComponent).
// Two OTHER combat data models exist in the source as parsed reference artifacts and
// are intentionally NOT used here:
//   - FBattleCardRow (BattleStructures.h) : TCG-style cards w/ BaseDamage + mutation.
//   - FR3ALN3TBattleStats (BattleStructures.h) : 1000-scale stat matrix.
// Those are not wired into any manager. Do not migrate Gap B onto them.
//
// Design boundary (see Architecture_Overview): NetPs live in the N3T (Cyberspace) plane;
// they only bleed into the R3AL overworld in rare, gated events. FEnemyDef therefore
// carries HomeDimension so spawn-gating can distinguish "realm-native" vs "bleed" spawns.

#pragma once

#include "CoreMinimal.h"
#include "BattleGridTypes.h"                          // EBattleElementType, FGridCoord
#include "BattleChipTypes.h"                          // FBattleChip, EChipCode (Greek), EChipClass
#include "../../Gameplay/Characters/R3ALN3T_NetPStructures.h" // FR3ALN3TNetPProfileRow, ENetPArchetype
#include "MythosGameTypes.h"                          // EMythosElement (run-flavor only)
#include "TrinityMatrixTypes.h"                       // G10: EElement (canon-21 bridge)
#include "../../Gameplay/World/R3ALN3T_WorldStructures.h"     // ER3ALN3TLayer
// FVirusDef is the source model for MakeEnemyDefFromVirus. Forward-declared here so the
// free-function declaration (line ~105) compiles without pulling in the manager header
// (which would re-create the .h cycle: R3ALN3T_BattleManager.h -> CombatTypes.h -> ...).
// The FULL definition is included in CombatTypes.cpp only.
struct FVirusDef;
#include "CombatTypes.generated.h"

// What produced this enemy — lets grid placement + rewards branch on origin.
UENUM(BlueprintType)
enum class EEnemySource : uint8
{
	Virus,   // legacy MMBN-style virus
	NetP,    // NetP (lives in N3T; R3AL appearance = bleed)
	Boss
};

// THE unified enemy definition. Viruses and NetPs both convert INTO this.
// It exposes everything both consumers need:
//   - Grid placement: EnemyID, DisplayName, Archetype, HomeDimension, SpawnCoord.
//   - Chip/damage math: HP/MaxHP, Attack, Shield, Element.
//   - Rewards: ZReward, DropRate, ChipDrops.
USTRUCT(BlueprintType)
struct FEnemyDef
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")
	FName EnemyID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")
	EEnemySource Source = EEnemySource::Virus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")
	ENetPArchetype Archetype = ENetPArchetype::LogicGate; // meaningful for NetP source

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	ER3ALN3TLayer HomeDimension = ER3ALN3TLayer::Cyberspace; // NetP native plane

	// Grid placement. Cols 4-7 = enemy side (see FGridCoord::GetSide).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	FGridCoord SpawnCoord = FGridCoord(4, 1);

	// Combat stats (MMBN scale, matches FVirusDef range).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	int32 HP = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	int32 MaxHP = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	int32 Attack = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	int32 Shield = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	EBattleElementType Element = EBattleElementType::None;

	// Rewards
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rewards")
	int32 ZReward = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rewards")
	float DropRate = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rewards")
	TArray<FName> ChipDrops;

	// True only for NetPs whose HomeDimension != Reality AND who have bled through.
	// Spawn-gating should require this (or a deliberate Realm event) before a NetP
	// can appear on the R3AL overworld.
	bool IsBleedSpawn() const
	{
		return Source == EEnemySource::NetP && HomeDimension != ER3ALN3TLayer::Reality;
	}
};

// ---- Conversions (free functions, defined in CombatTypes.cpp) ----
// Virus -> enemy (drop-in; preserves existing balance).
FEnemyDef MakeEnemyDefFromVirus(const FVirusDef& V);

// NetP -> enemy. THIS is the stat-scaling surface Gap B exists to review.
//   CoreStabilityIndex (100) -> HP (with BaseProcessingLevel variance)
//   BaseProcessingLevel (1+) -> Attack
//   BaseThroughputSpeed (300) -> ZReward
//   Archetype -> CombatElement + Shield
// NetP -> Enemy (G4 fix): honors the bound NetP's canon-21 element (EElement) when
// provided, bridging it into the 7-wheel combat element; archetype map is fallback
// only when BoundElement is None (unbound / DataTable-only spawn).
FEnemyDef MakeEnemyDefFromNetP(const FR3ALN3TNetPProfileRow& N,
    EElement BoundElement = EElement::None);

// ---- Element unification (REQUIRED before any multiplier math) ----
// EMythosElement is RUN-FLAVOR ONLY (career screen). Combat compares EBattleElementType exclusively.
EBattleElementType ToBattleElement(EMythosElement E);

// The single source of truth for chip/target element interaction.
// Returns a multiplier applied to summed chip Power (TPA). No type-punning: both args are
// EBattleElementType, so comparisons are always valid. Precedence (highest wins, no stacking):
//   same element (chip==target)  x1.5
//   panel buff   (chip==panel)   x1.25
//   strong-against (wheel)        x2.0
//   weak-against (reverse wheel)  x0.5
//   neutral                      x1.0
float EvaluateElementMultiplier(
	EBattleElementType ChipElement,
	EBattleElementType TargetElement,
	EBattleElementType PanelElement = EBattleElementType::None);

// G10 (element unification): bridge between the 7-wheel combat enum and the
// canon-21 element system. Combat structs store EBattleElementType (7-wheel);
// the canon matrix (UElementWheelCalculator) consumes EElement (21). These map
// the 7-wheel subset into canon-21 so combat math uses the verified 21x21 table.
// Holy has no canon-21 equivalent -> mapped to Light (closest). All other
// canon-21 elements have no 7-wheel counterpart and only arise via EElement.
EElement ToEElement(EBattleElementType Battle);
EBattleElementType ToBattleElement(EElement Canon);

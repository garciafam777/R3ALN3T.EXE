// ElementWheelCalculator.cpp — full combat damage (Nyx/engine-dev)
// LOCKED HOLY/VOID RULE (CEO-approved):
//   * Wheel: Fire>Wood>Wind>Elec>Aqua>Fire (each beats next). Holy/Void/None = neutral 1.0x.
//   * If any OMEGA present AND chip element is Holy/Void AND chip tier is BELOW ALPHA
//     (OMICRON only, per EOmegaCareerTier OMICRON=0 < ALPHA=1): chip is NULLIFIED (0 dmg).
//   * EXCEPTION: if the wielder is OMEGA-tier, Holy/Void deals FULL normal damage (1.0x)
//     regardless of sub-ALPHA tier.
//   * ALPHA-tier-or-higher Holy/Void: normal (1.0x) even with OMEGA present.
#include "ElementWheelCalculator.h"

// 5-element combat cycle; Holy/Void/None handled as neutral.
static const EBattleElementType Cycle[] = {
	EBattleElementType::Fire, EBattleElementType::Wood, EBattleElementType::Wind,
	EBattleElementType::Elec, EBattleElementType::Aqua
};

float UElementWheelCalculator::ElementMultiplier(EBattleElementType Att, EBattleElementType Def)
{
	if (Att == EBattleElementType::Holy || Att == EBattleElementType::Void ||
		Att == EBattleElementType::None || Def == EBattleElementType::Holy ||
		Def == EBattleElementType::Void || Def == EBattleElementType::None)
		return 1.0f;

	int32 ai = -1, di = -1;
	for (int32 i = 0; i < 5; ++i)
	{
		if (Cycle[i] == Att) ai = i;
		if (Cycle[i] == Def) di = i;
	}
	if (ai < 0 || di < 0) return 1.0f;
	if (Cycle[(ai + 1) % 5] == Def) return 2.0f; // attacker beats defender
	if (Cycle[(di + 1) % 5] == Att) return 0.5f; // defender beats attacker
	return 1.0f;
}

float UElementWheelCalculator::CalculateCSIPenalty(const FR3ALN3TNetPStatus& Target,
	const TArray<FR3ALN3TNetPStatus>& ActiveOMEGAs)
{
	float mult = 1.0f;
	bool bPrime = false;
	for (const FR3ALN3TNetPStatus& O : ActiveOMEGAs)
	{
		if (O.SupremacyTier == ESupremacyTier::PRIME) bPrime = true;
		if (O.SupremacyTier == ESupremacyTier::ELEMENTAL && O.DomainElement == Target.Element)
			mult *= 0.50f; // matching-domain elemental OMEGA: -50% CSI
	}
	if (bPrime) mult *= 0.75f; // prime: all non-OMEGA -25% (stacks multiplicatively)
	return mult; // e.g. 0.375 = prime + matching elemental
}

// LOCKED Holy/Void rule.
bool UElementWheelCalculator::IsChipNullified(EBattleElementType ChipElement, EOmegaCareerTier ChipTier,
	const TArray<FR3ALN3TNetPStatus>& ActiveOMEGAs, bool bAttackerIsOMEGATier)
{
	if (bAttackerIsOMEGATier) return false; // exception: OMEGA-tier wielder -> full damage
	if (ChipElement != EBattleElementType::Holy && ChipElement != EBattleElementType::Void) return false;
	// "Below ALPHA" = OMICRON tier only (EOmegaCareerTier: OMICRON=0, ALPHA=1).
	// FLAG: design may intend a wider bottom band; confirm with Chronos.
	if (static_cast<uint8>(ChipTier) < static_cast<uint8>(EOmegaCareerTier::ALPHA))
	{
		for (const FR3ALN3TNetPStatus& O : ActiveOMEGAs)
			if (O.SupremacyTier == ESupremacyTier::ELEMENTAL && O.DomainElement == ChipElement) return true;
	}
	return false;
}

float UElementWheelCalculator::CalculateDamage(const FR3ALN3TBattleChip& Attacker,
	const FR3ALN3TNetPStatus& Defender, const TArray<FR3ALN3TNetPStatus>& ActiveOMEGAs,
	bool bAttackerIsOMEGATier)
{
	if (IsChipNullified(Attacker.Element, Attacker.Tier, ActiveOMEGAs, bAttackerIsOMEGATier))
		return 0.0f;
	const float ElementMult = ElementMultiplier(Attacker.Element, Defender.Element);
	const float CSIMod = FMath::Clamp(Defender.CSI / 100.f, 0.f, 1.f); // CSI 0-100 -> 0..1
	const float SupremacyMod = CalculateCSIPenalty(Defender, ActiveOMEGAs);
	return Attacker.Damage * ElementMult * CSIMod * SupremacyMod;
}

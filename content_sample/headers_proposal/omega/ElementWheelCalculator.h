// ElementWheelCalculator.h - full damage calc (Task 5, PROPOSAL, Nyx/DevOps)
// REVIEW-ONLY. Extends ElementWheel.h + OMEGASupremacyCalculator.h.
// Wheel: Fire->Wood->Wind->Elec->Aqua->Fire (cycle); Holy/Void special.
#pragma once
#include "CoreMinimal.h"
#include "NetPTypes.h"
#include "NetPStatusData.h"
#include "ElementWheel.h"
#include "OMEGASupremacyCalculator.h"

struct FBattleChip
{
    EElement Element;
    int32 BaseDamage;
    ECareerTier Tier;
};

class R3ALN3T_EXE_API UElementWheelCalculator
{
public:
    // Wheel multiplier: Fire>Wood>Wind>Elec>Aqua>Fire cycle (each beats next). Holy/Void neutral to cycle.
    static float ElementMultiplier(EElement Attacker, EElement Defender)
    {
        static const EElement Cycle[] = {EElement::Fire, EElement::Wood, EElement::Wind,
                                          EElement::Elec, EElement::Aqua, EElement::Fire};
        // note: Holy/Void handled as neutral (1.0) unless OMEGA supremacy applies
        if (Attacker == EElement::Holy || Attacker == EElement::Void ||
            Defender == EElement::Holy || Defender == EElement::Void) return 1.0f;
        int32 a=-1,d=-1;
        const EElement C[] = {EElement::Fire,EElement::Wood,EElement::Wind,EElement::Elec,EElement::Aqua};
        for(int i=0;i<5;i++){ if(C[i]==Attacker)a=i; if(C[i]==Defender)d=i; }
        if(a<0||d<0) return 1.0f;
        if(C[(a+1)%5]==Defender) return 2.0f;   // attacker beats defender
        if(C[(d+1)%5]==Attacker) return 0.5f;   // defender beats attacker
        return 1.0f;
    }

    // Full formula: BaseDamage * ElementMult * CSIMod * SupremacyMod * TierCheck
    static float CalculateDamage(const FBattleChip& Attacker, const FNetPStatusData& Defender,
                                 const TArray<FNetPStatusData>& ActiveOMEGAs)
    {
        float dmg = (float)Attacker.BaseDamage;
        dmg *= ElementMultiplier(Attacker.Element, Defender.Element);

        // CSI modifier: defender CSI as 0..1 efficiency (higher = tougher)
        float csiMod = FMath::Clamp((float)Defender.CSI / 100.f, 0.f, 1.f); // 0..1
        dmg *= (0.5f + 0.5f * csiMod); // CSI 100 -> x1.0, CSI 0 -> x0.5

        // Supremacy modifier (CSI penalty from OMEGA presence)
        float supremacy = FOMEGASupremacyCalculator::CalculateCSIPenalty(Defender, ActiveOMEGAs);
        dmg *= supremacy;

        // Tier check: Holy/Void chip below ALPHA nullified if matching OMEGA present
        if (FOMEGASupremacyCalculator::IsChipNullified(Attacker.Element, Attacker.Tier, ActiveOMEGAs))
            return 0.0f;

        return FMath::Max(0.f, dmg);
    }
};

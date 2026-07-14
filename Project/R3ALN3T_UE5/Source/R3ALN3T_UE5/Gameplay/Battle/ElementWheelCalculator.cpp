// ElementWheelCalculator.cpp — 21-element matrix combat (CEO 07.13 canon)
#include "ElementWheelCalculator.h"
#include "ElementMatchupTable.h"

// matrix index for an EElement (MUST match ElementMatchup order: Fire,Aqua,Elec,Ice,Wind,Earth,Light,Dark,Void,Metal,Nature,Sound,Gravity,Time,Blood,Poison,Crystal,Plasma,Wood,Null,Glitch)
static int32 ElementIndex(EElement E)
{
    switch (E)
    {
        case EElement::Fire:    return 0;  case EElement::Aqua:     return 1;
        case EElement::Elec:    return 2;  case EElement::Ice:      return 3;
        case EElement::Wind:    return 4;  case EElement::Earth:    return 5;
        case EElement::Light:   return 6;  case EElement::Dark:     return 7;
        case EElement::Void:    return 8;  case EElement::Metal:    return 9;
        case EElement::Nature:  return 10; case EElement::Sound:    return 11;
        case EElement::Gravity: return 12; case EElement::Time:     return 13;
        case EElement::Blood:   return 14; case EElement::Poison:   return 15;
        case EElement::Crystal: return 16; case EElement::Plasma:   return 17;
        case EElement::Wood:    return 18; case EElement::Null:     return 19;
        case EElement::Glitch:  return 20;
        default: return -1; // None
    }
}

float UElementWheelCalculator::ElementMultiplier(EElement Attacker, EElement Defender)
{
    if (Attacker == EElement::None || Defender == EElement::None) return 1.0f;
    const int32 ai = ElementIndex(Attacker), di = ElementIndex(Defender);
    if (ai < 0 || di < 0) return 1.0f;
    if (ai == di) return 0.5f;                       // mirror clash (SELF)
    return ElementMatchup[ai][di];                   // 1.25 (WIN) / 0.75 (LOSS) from matrix
}

int32 UElementWheelCalculator::CalculateDamage(int32 BaseDamage, EElement Attacker, EElement Defender,
    float ProgramMult, int32 TargetDEF, float CritMult, float Vulnerability)
{
    const float Elem = ElementMultiplier(Attacker, Defender);
    float dmg = (static_cast<float>(BaseDamage) * Elem * ProgramMult) - static_cast<float>(TargetDEF);
    dmg *= CritMult * Vulnerability;
    return FMath::Max(0, FMath::RoundToInt(dmg));
}

bool UElementWheelCalculator::CanUseChipOfTier(EGreekTier NetPTier, EGreekTier ChipTier)
{
    // Higher enum value = higher tier (OmicronPSI=0 .. Omega=7). Omega uses all.
    return static_cast<uint8>(ChipTier) <= static_cast<uint8>(NetPTier);
}

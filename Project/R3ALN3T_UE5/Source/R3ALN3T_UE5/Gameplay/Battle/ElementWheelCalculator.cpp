// ElementWheelCalculator.cpp — 18-element combat (Nyx/engine-dev v2)
#include "ElementWheelCalculator.h"

// 9 opposite pairs (Book 5). Index = counter element of the key.
static const TMap<EElement, EElement>& CounterMap()
{
    static const TMap<EElement, EElement> M = {
        {EElement::Fire,   EElement::Aqua},
        {EElement::Aqua,   EElement::Fire},
        {EElement::Elec,   EElement::Wood},
        {EElement::Wood,   EElement::Elec},
        {EElement::Wind,   EElement::Earth},
        {EElement::Earth,  EElement::Wind},
        {EElement::Light,  EElement::Dark},
        {EElement::Dark,   EElement::Light},
        {EElement::Null,   EElement::Glitch},
        {EElement::Glitch, EElement::Null},
        {EElement::Plasma, EElement::Crystal},
        {EElement::Crystal,EElement::Plasma},
        {EElement::Time,   EElement::Gravity},
        {EElement::Gravity,EElement::Time},
        {EElement::Sound,  EElement::Metal},
        {EElement::Metal,  EElement::Sound},
        {EElement::Poison, EElement::Nature},
        {EElement::Nature, EElement::Poison}
    };
    return M;
}

float UElementWheelCalculator::ElementMultiplier(EElement Attacker, EElement Defender)
{
    if (Attacker == EElement::None || Defender == EElement::None) return 1.0f;
    if (Attacker == Defender) return 0.5f;                       // mirror clash
    const auto& C = CounterMap();
    if (const EElement* Counter = C.Find(Attacker))              // Attacker beats its counter?
    {
        if (*Counter == Defender) return 1.5f;                  // super-effective
    }
    if (const EElement* AttCounter = C.Find(Defender))           // Defender's counter = Attacker's pair?
    {
        if (*AttCounter == Attacker) return 0.75f;              // resisted (paired)
    }
    return 1.0f;                                                 // neutral
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

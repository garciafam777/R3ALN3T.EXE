// NetPRandomizer.cpp — G4 implementation.
#include "NetPRandomizer.h"
#include "Kismet/KismetMathLibrary.h"

FR3ALN3TNetPStatus UNetPRandomizer::RandomizeNetP()
{
    FR3ALN3TNetPStatus NetP;

    // Tier: weighted so the strongest allowed (Zeta) is scarcest. weights[0]=weakest highest.
    int32 Weights[4] = { 4, 3, 2, 1 };
    const int32 Total = Weights[0] + Weights[1] + Weights[2] + Weights[3];
    int32 Roll = FMath::RandRange(1, Total);
    int32 Idx = 0, Accum = 0;
    for (int32 i = 0; i < 4; ++i) { Accum += Weights[i]; if (Roll <= Accum) { Idx = i; break; } }
    NetP.Tier = AllowedTiers[Idx]; // ceiling ZETA, never OMEGA

    // Element: random canon-21 (indices 1..21; EElement::None == 0 is excluded by design).
    // Canon elements are Fire(1) .. Void(21).
    static constexpr int32 CanonElementFirst = 1;   // EElement::Fire
    static constexpr int32 CanonElementLast  = 21;  // EElement::Void
    NetP.Element = static_cast<EElement>(FMath::RandRange(CanonElementFirst, CanonElementLast));

    // Baseline stats by tier band (kept inside canon ranges; not balance-final).
    switch (NetP.Tier)
    {
        case EGreekTier::Zeta:      NetP.HP = FMath::RandRange(180, 320); NetP.ATK = FMath::RandRange(30, 65); break;
        case EGreekTier::PSI:       NetP.HP = FMath::RandRange(8, 18);   NetP.ATK = FMath::RandRange(2, 5);   break;
        case EGreekTier::Omicron:   NetP.HP = FMath::RandRange(20, 45);  NetP.ATK = FMath::RandRange(4, 10);  break;
        default:                    NetP.HP = FMath::RandRange(10, 25);  NetP.ATK = FMath::RandRange(3, 7);   break; // OmicronPSI
    }
    NetP.RAPID  = FMath::RandRange(1, 30) / 100.f;
    NetP.CHARGE = FMath::RandRange(2, 40);
    NetP.DEF    = FMath::RandRange(1, 35);
    NetP.SPD    = FMath::RandRange(1, 8);
    NetP.Soul   = ESoulState::Neutral;
    NetP.Construct = ENetPConstruct::Trinity;
    return NetP;
}

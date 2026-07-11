// OMEGASupremacyCalculator.cpp - Supremacy Clause implementation (PROPOSAL, Nyx/DevOps)
// REVIEW-ONLY. Faithful to spec; verified via ad-hoc logic check (no UE compile here).
#include "NetPTypes.h"
#include "NetPStatusData.h"
#include "OMEGASupremacyCalculator.h"

bool FOMEGASupremacyCalculator::IsOMEGAPresent(const TArray<FNetPStatusData>& A)
{
    for (const FNetPStatusData& N : A)
        if (N.SupremacyTier == ESupremacyTier::ELEMENTAL ||
            N.SupremacyTier == ESupremacyTier::PRIME) return true;
    return false;
}

bool FOMEGASupremacyCalculator::IsOMEGAPrimePresent(const TArray<FNetPStatusData>& A)
{
    for (const FNetPStatusData& N : A)
        if (N.SupremacyTier == ESupremacyTier::PRIME) return true;
    return false;
}

EElement FOMEGASupremacyCalculator::GetDominantOMEGADomain(const TArray<FNetPStatusData>& A)
{
    for (const FNetPStatusData& N : A)
        if (N.SupremacyTier == ESupremacyTier::ELEMENTAL) return N.DomainElement;
    return EElement::Void; // fallback
}

float FOMEGASupremacyCalculator::CalculateCSIPenalty(const FNetPStatusData& Target,
                                                     const TArray<FNetPStatusData>& ActiveOMEGAs)
{
    if (Target.SupremacyTier == ESupremacyTier::ELEMENTAL ||
        Target.SupremacyTier == ESupremacyTier::PRIME) return 1.0f; // OMEGAs immune

    float mult = 1.0f;
    bool prime = IsOMEGAPrimePresent(ActiveOMEGAs);
    if (prime) mult *= 0.75f; // -25% all non-OMEGA

    for (const FNetPStatusData& O : ActiveOMEGAs)
    {
        if (O.SupremacyTier == ESupremacyTier::ELEMENTAL &&
            O.DomainElement == Target.Element) // matching domain
        {
            mult *= 0.50f; // -50% CSI (stacks multiplicatively w/ prime)
            break;
        }
    }
    return mult; // e.g. 0.375 = prime+elemental-match
}

bool FOMEGASupremacyCalculator::IsChipNullified(EElement ChipElement, ECareerTier ChipTier,
                                                const TArray<FNetPStatusData>& ActiveOMEGAs)
{
    if (ChipElement != EElement::Holy && ChipElement != EElement::Void) return false;
    if (static_cast<int32>(ChipTier) > static_cast<int32>(ECareerTier::ALPHA)) // below ALPHA (BETA..OMICRON)
    {
        for (const FNetPStatusData& O : ActiveOMEGAs)
            if (O.SupremacyTier == ESupremacyTier::ELEMENTAL &&
                O.DomainElement == ChipElement) return true;
    }
    return false;
}

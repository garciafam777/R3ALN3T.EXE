// OMEGASupremacyCalculator.h - Supremacy Clause combat rules (PROPOSAL, Nyx/DevOps)
// REVIEW-ONLY. Implements the OMEGA Overlord supremacy penalties from the spec.
#pragma once
#include "CoreMinimal.h"
#include "NetPTypes.h"
#include "NetPStatusData.h"

class R3ALN3T_EXE_API FOMEGASupremacyCalculator
{
public:
    static bool IsOMEGAPresent(const TArray<FNetPStatusData>& ActiveNetPs);
    static bool IsOMEGAPrimePresent(const TArray<FNetPStatusData>& ActiveNetPs);
    static EElement GetDominantOMEGADomain(const TArray<FNetPStatusData>& ActiveNetPs);

    // CSI penalty (0 = none, negative multiplier applied by caller).
    // Elemental OMEGA: matching domain -> -50% CSI on non-OMEGA.
    // Prime present: ALL non-OMEGA -> -25% CSI (stacks w/ elemental if matching).
    static float CalculateCSIPenalty(const FNetPStatusData& Target,
                                     const TArray<FNetPStatusData>& ActiveOMEGAs);

    // Holy/Void chips below ALPHA tier NULLIFIED when their elemental OMEGA is present.
    static bool IsChipNullified(EElement ChipElement, ECareerTier ChipTier,
                                const TArray<FNetPStatusData>& ActiveOMEGAs);
};

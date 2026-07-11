// CareerTier.h - OMEGA..OMICRON progression enum + helpers
// PROPOSAL (Nyx/DevOps) - for Chatsurfer review; NOT yet in Source/.
#pragma once
#include "CoreMinimal.h"
#include "CareerTier.generated.h"

// 16-rank hierarchy, OMEGA (highest) -> OMICRON (lowest)
UENUM(BlueprintType)
enum class ECareerTier : uint8
{
    OMEGA, ALPHA, BETA, GAMMA, DELTA, EPSILON, ZETA, ETA,
    THETA, IOTA, KAPPA, LAMBDA, MU, NU, XI, OMICRON
};

namespace R3ALN3TCareer
{
    // rank order index: OMEGA=0 (top) .. OMICRON=15 (bottom)
    inline int32 TierOrder(ECareerTier T)
    {
        return static_cast<int32>(T); // enum declared high->low already
    }
    inline bool Outranks(ECareerTier A, ECareerTier B)
    {
        return TierOrder(A) < TierOrder(B); // lower index = higher tier
    }
    inline const TCHAR* ToString(ECareerTier T)
    {
        switch (T)
        {
            case ECareerTier::OMEGA:   return TEXT("OMEGA");
            case ECareerTier::ALPHA:   return TEXT("ALPHA");
            case ECareerTier::BETA:    return TEXT("BETA");
            case ECareerTier::GAMMA:   return TEXT("GAMMA");
            case ECareerTier::DELTA:   return TEXT("DELTA");
            case ECareerTier::EPSILON: return TEXT("EPSILON");
            case ECareerTier::ZETA:    return TEXT("ZETA");
            case ECareerTier::ETA:     return TEXT("ETA");
            case ECareerTier::THETA:   return TEXT("THETA");
            case ECareerTier::IOTA:    return TEXT("IOTA");
            case ECareerTier::KAPPA:   return TEXT("KAPPA");
            case ECareerTier::LAMBDA:  return TEXT("LAMBDA");
            case ECareerTier::MU:      return TEXT("MU");
            case ECareerTier::NU:      return TEXT("NU");
            case ECareerTier::XI:      return TEXT("XI");
            case ECareerTier::OMICRON: return TEXT("OMICRON");
            default:                   return TEXT("?");
        }
    }
}

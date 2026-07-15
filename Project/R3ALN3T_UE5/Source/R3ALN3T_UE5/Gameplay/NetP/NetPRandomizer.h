// NetPRandomizer.h — G4: abuse-safe NetP randomizer (C++ port of generate_cards.randomize_netp).
// Tier ceiling = ZETA (starter-grade); excludes OMEGA + EPSILON..ALPHA. Same envelope as the
// verified Python (5000 rolls -> 0 OMEGA / 0 over-ZETA).
#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../../Core/Types/TrinityMatrixTypes.h"
#include "NetPRandomizer.generated.h"

UCLASS()
class R3ALN3T_UE5_API UNetPRandomizer : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    // G4 entry point. Call from a UMG "Randomize NetP" button OnClicked.
    // Returns a rank-capped, abuse-safe random NetP.
    UFUNCTION(BlueprintCallable, Category = "R3ALN3T|NetP")
    static FR3ALN3TNetPStatus RandomizeNetP();

private:
    // Allowed tiers for the randomizer (weakest..strongest). Ceiling = ZETA.
    // C++ EGreekTier members are {OmicronPSI=0, Zeta=1, Epsilon=2, Delta=3,
    //   Gamma=4, Beta=5, Alpha=6, Omega=7}. Python RANDOMIZER_MAX_TIER = ZETA.
    static constexpr EGreekTier AllowedTiers[2] = {
        EGreekTier::OmicronPSI, EGreekTier::Zeta
    };
};

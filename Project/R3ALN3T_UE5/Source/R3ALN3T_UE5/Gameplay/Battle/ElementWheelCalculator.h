// ElementWheelCalculator.h — 21-element matrix combat (CEO 07.13 canon)
#pragma once
#include "CoreMinimal.h"
#include "../../Core/Types/TrinityMatrixTypes.h"
#include "ElementWheelCalculator.generated.h"

UCLASS()
class R3ALN3T_UE5_API UElementWheelCalculator : public UObject
{
    GENERATED_BODY()
public:
    // Elemental multiplier vs defender element: looked up from the 21x21
    // ElementMatchup table (WIN=1.25, LOSS=0.75, mirror/SELF=0.5, None=1.0 neutral).
    UFUNCTION(BlueprintPure, Category="R3ALN3T|Combat")
    static float ElementMultiplier(EElement Attacker, EElement Defender);

    // Full damage (Book 5 formula): (base * elem * program) - DEF, x crit, x vuln.
    UFUNCTION(BlueprintPure, Category="R3ALN3T|Combat")
    static int32 CalculateDamage(int32 BaseDamage, EElement Attacker, EElement Defender,
        float ProgramMult, int32 TargetDEF, float CritMult = 1.0f, float Vulnerability = 1.0f);

    // Chip-folder rank gating: NetP may use chips <= its Greek tier.
    UFUNCTION(BlueprintPure, Category="R3ALN3T|Combat")
    static bool CanUseChipOfTier(EGreekTier NetPTier, EGreekTier ChipTier);
};

// ElementWheelCalculator.h — 18-element combat (Nyx/engine-dev v2, Trinity Matrix canon)
#pragma once
#include "CoreMinimal.h"
#include "../../Core/Types/TrinityMatrixTypes.h"
#include "ElementWheelCalculator.generated.h"

UCLASS()
class R3ALN3T_UE5_API UElementWheelCalculator : public UObject
{
    GENERATED_BODY()
public:
    // Elemental multiplier vs defender element (Book 5): counter=1.5x, pair=0.75x,
    // same=0.5x (mirror clash), else 1.0x.
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

// BattleChip.h - MMBN-style chip (damage, element, memory cost)
// PROPOSAL (Nyx/DevOps) - for Chatsurfer review; NOT yet in Source/.
#pragma once
#include "CoreMinimal.h"
#include "BattleChip.generated.h"
#include "ElementWheel.h"

UENUM(BlueprintType)
enum class EChipClass : uint8 { Standard, Mega, Giga, Dark, Support };

USTRUCT(BlueprintType)
struct FR3ALN3TBattleChip
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString ID;        // CHIP-####
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Name;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) EBattleElementType Element; // canonical 7-wheel
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Damage;     // MB damage dealt
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 MB;         // memory cost (MB used in folder)
    UPROPERTY(EditAnywhere, BlueprintReadWrite) EChipClass Class;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Description;

    // resolve this chip's elemental multiplier vs a defender element
    float MultiplierVs(EBattleElementType Defender) const
    {
        return UElementWheel::Multiplier(Element, Defender);
    }
};

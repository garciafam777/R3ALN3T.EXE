// ElementWheel.h - canonical 7-element matchup logic
// PROPOSAL (Nyx/DevOps) - for Chatsurfer review; NOT yet in Source/.
// Wheel (BattleGridTypes.h:19): None, Fire, Aqua, Elec, Wood, Wind, Holy, Void
// Cycle: Fire > Aqua > Elec > Wood > Wind > Holy > Void > Fire  (each beats the next)
#pragma once
#include "CoreMinimal.h"
#include "ElementWheel.generated.h"

UENUM(BlueprintType)
enum class EBattleElementType : uint8
{
    None, Fire, Aqua, Elec, Wood, Wind, Holy, Void
};

UCLASS()
class UR3ALN3TElementWheel : public UObject
{
    GENERATED_BODY()
public:
    // returns damage multiplier: 2.0 strong, 0.5 weak, 1.0 neutral/None
    static float Multiplier(EBattleElementType Attacker, EBattleElementType Defender)
    {
        if (Attacker == EBattleElementType::None || Defender == EBattleElementType::None)
            return 1.0f;
        static const EBattleElementType Cycle[] = {
            EBattleElementType::Fire, EBattleElementType::Aqua, EBattleElementType::Elec,
            EBattleElementType::Wood, EBattleElementType::Wind, EBattleElementType::Holy,
            EBattleElementType::Void };
        int32 a = IndexOf(Attacker), d = IndexOf(Defender);
        if (a < 0 || d < 0) return 1.0f;
        if (Cycle[(a + 1) % 7] == Defender) return 2.0f; // attacker beats defender
        if (Cycle[(d + 1) % 7] == Attacker) return 0.5f; // defender beats attacker
        return 1.0f;
    }
private:
    static int32 IndexOf(EBattleElementType E)
    {
        switch (E)
        {
            case EBattleElementType::Fire: return 0;
            case EBattleElementType::Aqua: return 1;
            case EBattleElementType::Elec: return 2;
            case EBattleElementType::Wood: return 3;
            case EBattleElementType::Wind: return 4;
            case EBattleElementType::Holy: return 5;
            case EBattleElementType::Void: return 6;
            default: return -1;
        }
    }
};
using UElementWheel = UR3ALN3TElementWheel;

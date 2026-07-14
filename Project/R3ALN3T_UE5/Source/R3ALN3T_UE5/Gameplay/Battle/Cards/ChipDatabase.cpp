// ChipDatabase.cpp

#include "ChipDatabase.h"

void UChipDatabase::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    PopulateSliceChips();
}

void UChipDatabase::PopulateSliceChips()
{
    ChipMap.Empty();

    // Slice starter folder: 8 chips covering all 4 wheel elements + None, so the
    // Rotterdam encounter can exercise the full EvaluateElementMultiplier matrix
    // (super-effective, resisted, neutral, panel-fold) with a small, testable set.
    //
    // Element enum values are EBattleElementType: None, Fire, Aqua, Elec, Wood, Wind, Holy, Void.

    auto AddChip = [this](FName Code, const FString& Name, EBattleElementType Elem, int32 Power, float Gauge, const FString& Pattern)
    {
        FChipDef Def;
        Def.ChipCode = Code;
        Def.DisplayName = Name;
        Def.Element = Elem;
        Def.BasePower = Power;
        Def.GaugeCost = Gauge;
        Def.TargetPattern = Pattern;
        ChipMap.Add(Code, Def);
    };

    AddChip(TEXT("Alpha"),   TEXT("Alpha Shot"),   EBattleElementType::Fire, 40, 1.0f, TEXT("SingleTarget"));
    AddChip(TEXT("Beta"),    TEXT("Beta Shot"),    EBattleElementType::Fire, 40, 1.0f, TEXT("SingleTarget"));
    AddChip(TEXT("Gamma"),   TEXT("Gamma Shot"),   EBattleElementType::Fire, 40, 1.0f, TEXT("SingleTarget"));
    AddChip(TEXT("Delta"),   TEXT("Delta Wave"),   EBattleElementType::Aqua, 35, 1.0f, TEXT("Row"));
    AddChip(TEXT("Epsilon"), TEXT("Epsilon Bolt"), EBattleElementType::Elec, 30, 0.8f, TEXT("Column"));
    AddChip(TEXT("Zeta"),    TEXT("Zeta Root"),    EBattleElementType::Wood, 45, 1.2f, TEXT("SingleTarget"));
    AddChip(TEXT("Eta"),     TEXT("Eta Null"),     EBattleElementType::Void, 50, 1.5f, TEXT("SingleTarget"));
    AddChip(TEXT("Theta"),   TEXT("Theta Cannon"), EBattleElementType::None, 60, 1.5f, TEXT("SingleTarget"));
}

const FChipDef* UChipDatabase::FindChip(FName ChipCode) const
{
    return ChipMap.Find(ChipCode);
}

TArray<FName> UChipDatabase::GetSliceStarterFolder() const
{
    TArray<FName> Codes;
    ChipMap.GetKeys(Codes);
    return Codes;
}

float UChipDatabase::ResolveChipDamage(FName ChipCode, EBattleElementType DefenderElement) const
{
    const FChipDef* Chip = FindChip(ChipCode);
    if (!Chip)
    {
        UE_LOG(LogTemp, Warning, TEXT("ResolveChipDamage: unknown chip code %s"), *ChipCode.ToString());
        return 0.0f;
    }

    // G10: use canon-21 matrix (UElementWheelCalculator) bridged from 7-wheel combat enums.
    const float Multiplier = UElementWheelCalculator::ElementMultiplier(
    	ToEElement(Chip->Element), ToEElement(DefenderElement));
    return Chip->BasePower * Multiplier;
}

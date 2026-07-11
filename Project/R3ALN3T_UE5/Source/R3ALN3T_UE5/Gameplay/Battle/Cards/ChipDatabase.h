// ChipDatabase.h
// Slice-scoped Greek-code chip set (8-12 of the 108 Ghost Data pieces) and lookup by
// chip code for BattleManager / player folder logic.
//
// True-up notes vs the draft you supplied:
//   - EElementType does NOT exist in the repo. The real element enum is EBattleElementType
//     (BattleGridTypes.h: None, Fire, Aqua, Elec, Wood, Wind, Holy, Void). Renamed.
//   - EvaluateElementMultiplier(EBattleElementType, EBattleElementType, EBattleElementType=...)
//     lives in CombatTypes.h and is verified by the UBT compile pass. Signature matches.
//   - Module API macro is R3ALN3T_UE5_API (not R3ALN3T_API).
// Nothing here depends on CombatTypes internals beyond the two names above, so it drops in
// additively on top of the already-compiling CombatTypes.cpp.

#pragma once

#include "CoreMinimal.h"
#include "../../../Core/Types/CombatTypes.h" // EBattleElementType, EvaluateElementMultiplier
#include "../../../Core/Types/SoulState.h"   // Gap C: ESoulFork
#include "Subsystems/GameInstanceSubsystem.h"
#include "ChipDatabase.generated.h"

USTRUCT(BlueprintType)
struct FChipDef
{
    GENERATED_BODY()

    // Greek-letter chip code, e.g. "Alpha", "Beta" — matches your 24-letter chip code system.
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName ChipCode = NAME_None;

    // Display name shown in the folder UI, separate from the code identity.
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FString DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    EBattleElementType Element = EBattleElementType::None;

    // Base power before element multiplier is applied.
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 BasePower = 0;

    // Gauge cost to play this chip in the real-time gauge (MMBN-style).
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float GaugeCost = 1.0f;

    // Optional: which grid panels this chip hits (e.g. single target, row, column).
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FString TargetPattern = TEXT("SingleTarget");

    // Gap C: the soul intent this chip carries. None for the slice chips (fork is
    // then classified from the combat outcome in PlayChip).
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    ESoulFork SoulFork = ESoulFork::None;
};

UCLASS()
class R3ALN3T_UE5_API UChipDatabase : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    // Returns nullptr if ChipCode isn't found — callers must check.
    const FChipDef* FindChip(FName ChipCode) const;

    // Slice-scoped starting folder: the subset of chip codes available in the
    // Rotterdam vertical slice. NOT the full 108 Ghost Data set.
    UFUNCTION(BlueprintCallable)
    TArray<FName> GetSliceStarterFolder() const;

    // Computes final damage for a chip played against a given defender element.
    UFUNCTION(BlueprintPure, Category = "Battle|GapB")
    float ResolveChipDamage(FName ChipCode, EBattleElementType DefenderElement) const;

    // (Re)builds the slice chip set. Public so a headless/harness path can populate it
    // without relying on subsystem Initialize order.
    void PopulateSliceChips();

private:
    UPROPERTY()
    TMap<FName, FChipDef> ChipMap;
};

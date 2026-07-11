// ElementWheelCalculator.h — full combat damage (Nyx/engine-dev, compile-ready)
#pragma once
#include "CoreMinimal.h"
#include "Core/Types/SoulBattleTypes.h"
#include "ElementWheelCalculator.generated.h"

USTRUCT(BlueprintType)
struct FR3ALN3TBattleChip
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EBattleElementType Element = EBattleElementType::None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Damage = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EOmegaCareerTier Tier = EOmegaCareerTier::OMICRON;
};

UCLASS()
class R3ALN3T_UE5_API UElementWheelCalculator : public UObject
{
	GENERATED_BODY()
public:
	// Full damage: Base * ElementMult * CSIMod * SupremacyMod * TierCheck
	UFUNCTION(BlueprintCallable, Category = "OMEGA|Combat")
	static float CalculateDamage(const FR3ALN3TBattleChip& Attacker,
	                            const FR3ALN3TNetPStatus& Defender,
	                            const TArray<FR3ALN3TNetPStatus>& ActiveOMEGAs,
	                            bool bAttackerIsOMEGATier);

	// Element multiplier on the 5-cycle (Holy/Void neutral; None neutral).
	UFUNCTION(BlueprintCallable, Category = "OMEGA|Combat")
	static float ElementMultiplier(EBattleElementType Att, EBattleElementType Def);

	// CSI modifier from OMEGA supremacy presence (elemental -50%, prime -25%, stack).
	UFUNCTION(BlueprintCallable, Category = "OMEGA|Combat")
	static float CalculateCSIPenalty(const FR3ALN3TNetPStatus& Target,
	                                 const TArray<FR3ALN3TNetPStatus>& ActiveOMEGAs);

	// Holy/Void below-ALPHA nullification when OMEGA present (unless attacker is OMEGA-tier).
	UFUNCTION(BlueprintCallable, Category = "OMEGA|Combat")
	static bool IsChipNullified(EBattleElementType ChipElement, EOmegaCareerTier ChipTier,
	                            const TArray<FR3ALN3TNetPStatus>& ActiveOMEGAs, bool bAttackerIsOMEGATier);
};

// BattleStagePanel.h
// One physical 3D panel tile — a beveled platform block, not a flat decal.
// Designed for a Smash-Bros-"Battlefield"-style floating stage: panels sit slightly
// apart with visible gaps/bevels so edge-lighting and bloom read clearly at 4K,
// and so individual panels can animate (raise/lower/crack/glow) independently.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BattleGridTypes.h"
#include "BattleStagePanel.generated.h"

class UStaticMeshComponent;
class UMaterialInstanceDynamic;

UCLASS()
class R3ALN3T_UE5_API ABattleStagePanel : public AActor
{
	GENERATED_BODY()

public:
	ABattleStagePanel();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGridCoord Coord;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* PanelMesh; // beveled box/platform mesh, e.g. a chamfered cube

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* EdgeGlowMesh; // thin inset outline mesh for the emissive border line

	// Sets base color (Tier/Rank/Element for player side, Location for enemy side).
	UFUNCTION(BlueprintCallable)
	void SetBaseColor(FLinearColor Color);

	// Drives the bright highlight pulse used when a unit is standing on / targeting this panel.
	UFUNCTION(BlueprintCallable)
	void SetHighlighted(bool bHighlighted, FLinearColor HighlightColor);

	// Plays the crack-and-fall animation, then disables collision/walkability.
	UFUNCTION(BlueprintCallable)
	void BreakPanel();

	// Smash-"Battlefield"-style gentle bob — call from a manager Tick or Timeline, not every panel ticking individually.
	UFUNCTION(BlueprintCallable)
	void SetBobOffset(float ZOffset);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UMaterialInstanceDynamic* PanelMID;

	UPROPERTY()
	UMaterialInstanceDynamic* EdgeMID;

	bool bIsBroken = false;
};

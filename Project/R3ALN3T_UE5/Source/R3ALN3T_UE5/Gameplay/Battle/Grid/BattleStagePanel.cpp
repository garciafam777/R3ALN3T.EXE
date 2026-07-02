// BattleStagePanel.cpp
#include "BattleStagePanel.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "../../../Core/Types/BattleGridTypes.h"

ABattleStagePanel::ABattleStagePanel()
{
	PrimaryActorTick.bCanEverTick = false;

	PanelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PanelMesh"));
	RootComponent = PanelMesh;
	// Assign a chamfered-box mesh in the editor — bevel reads MUCH better at 4K than
	// a hard 90-degree cube edge, avoids aliasing on the silhouette.

	EdgeGlowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EdgeGlowMesh"));
	EdgeGlowMesh->SetupAttachment(PanelMesh);
	// A thin inset frame mesh sitting just above the panel top face — this is what
	// gives you that crisp Tron-style glowing border line seen in the reference HUD,
	// translated into 3D. Keep it a separate mesh so its emissive material can pulse
	// independently of the panel base color.
}

void ABattleStagePanel::BeginPlay()
{
	Super::BeginPlay();

	if (PanelMesh->GetMaterial(0))
	{
		PanelMID = UMaterialInstanceDynamic::Create(PanelMesh->GetMaterial(0), this);
		PanelMesh->SetMaterial(0, PanelMID);
	}
	if (EdgeGlowMesh->GetMaterial(0))
	{
		EdgeMID = UMaterialInstanceDynamic::Create(EdgeGlowMesh->GetMaterial(0), this);
		EdgeGlowMesh->SetMaterial(0, EdgeMID);
	}
}

void ABattleStagePanel::SetBaseColor(FLinearColor Color)
{
	if (PanelMID)
	{
		PanelMID->SetVectorParameterValue(TEXT("BaseColor"), Color);
		PanelMID->SetVectorParameterValue(TEXT("EmissiveColor"), Color * 0.4f); // subtle ambient glow at rest
	}
	if (EdgeMID)
	{
		EdgeMID->SetVectorParameterValue(TEXT("EmissiveColor"), Color);
	}
}

void ABattleStagePanel::SetHighlighted(bool bHighlighted, FLinearColor HighlightColor)
{
	if (!EdgeMID) return;
	const float Intensity = bHighlighted ? 6.f : 1.f; // material should multiply EmissiveColor * Intensity into emissive output
	EdgeMID->SetScalarParameterValue(TEXT("EmissiveIntensity"), Intensity);
	if (bHighlighted)
	{
		EdgeMID->SetVectorParameterValue(TEXT("EmissiveColor"), HighlightColor);
	}
}

void ABattleStagePanel::BreakPanel()
{
	if (bIsBroken) return;
	bIsBroken = true;
	PanelMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// Trigger your Niagara crack/debris system here, then a Timeline dropping
	// PanelMesh's relative Z down and out of view, finishing with SetVisibility(false).
}

void ABattleStagePanel::SetBobOffset(float ZOffset)
{
	FVector Loc = GetActorLocation();
	Loc.Z = ZOffset;
	SetActorLocation(Loc);
}

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MythosHUD.generated.h"

class AMythosGameMode;

UCLASS()
class R3ALN3T_EXE_API AMythosHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

private:
	float LineY = 0.f;
	void DrawLineText(const FString& Text, float X, const FLinearColor& Color, float Scale = 1.f);
	void DrawHeader(AMythosGameMode* GM);
	void DrawStart(AMythosGameMode* GM);
	void DrawCareerSelect(AMythosGameMode* GM);
	void DrawElementSelect(AMythosGameMode* GM);
	void DrawWork(AMythosGameMode* GM);
	void DrawStoryChoice(AMythosGameMode* GM);
	void DrawBattle(AMythosGameMode* GM);
	void DrawEnding(AMythosGameMode* GM);
	void DrawPostGame(AMythosGameMode* GM);
};

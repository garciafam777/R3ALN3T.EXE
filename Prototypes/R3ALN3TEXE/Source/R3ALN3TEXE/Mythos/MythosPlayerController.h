#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MythosPlayerController.generated.h"

UCLASS()
class R3ALN3TEXE_API AMythosPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void PressOne();
	void PressTwo();
	void PressThree();
	void PressFour();
	void PressFive();
	void PressSix();
	void PressR();
	void PressSpace();
	void PressEnter();
	void HandleNumber(int32 Number);
};

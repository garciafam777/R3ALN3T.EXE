// Forces mouse visibility and instantiates the master viewport widget.
// No character/pawn is spawned — safe for title/splash screens.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MenuPlayerController.generated.h"

UCLASS()
class R3ALN3T_UE5_API AMenuPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void PressEnter();
	void PressEscape();
};

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "R3ALN3TCharacter.generated.h"

UCLASS()
class R3ALN3T_API AR3ALN3TCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AR3ALN3TCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};

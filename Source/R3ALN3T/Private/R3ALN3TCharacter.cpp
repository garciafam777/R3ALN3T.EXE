#include "R3ALN3TCharacter.h"

AR3ALN3TCharacter::AR3ALN3TCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Example component creation (uncomment if you add Camera/SpringArm includes):
	// CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	// CameraBoom->SetupAttachment(RootComponent);
	// FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	// FollowCamera->SetupAttachment(CameraBoom);
}

void AR3ALN3TCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AR3ALN3TCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AR3ALN3TCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind input here, e.g.:
	// PlayerInputComponent->BindAxis("MoveForward", this, &AR3ALN3TCharacter::MoveForward);
}

// R3ALN3TGameMode.cpp
#include "R3ALN3TGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

AR3ALN3TGameMode::AR3ALN3TGameMode()
{
	bGameStarted = false;
	CurrentIntroSequence = nullptr;
}

void AR3ALN3TGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Don't auto-start intro - wait for player input from main menu
	UE_LOG(LogTemp, Warning, TEXT("[GameMode] R3ALN3T GameMode loaded"));
}

void AR3ALN3TGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (NewPlayer)
	{
		NewPlayer->bShowMouseCursor = true;
		NewPlayer->SetInputMode(FInputModeGameAndUI());
	}
}

void AR3ALN3TGameMode::StartNewGame()
{
	if (bGameStarted)
	{
		UE_LOG(LogTemp, Warning, TEXT("[GameMode] Game already started"));
		return;
	}

	bGameStarted = true;

	UE_LOG(LogTemp, Warning, TEXT("[GameMode] Starting new game - spawning intro sequence"));

	// Spawn intro sequence actor
	SpawnIntroSequence();

	// Hide main menu UI (assumes it exists)
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC && PC->GetInputMode().GetWidgetToFocus().IsValid())
	{
		// Main menu widget should be destroyed or hidden
	}
}

void AR3ALN3TGameMode::LoadGame(const FString& SaveSlot)
{
	if (bGameStarted)
	{
		UE_LOG(LogTemp, Warning, TEXT("[GameMode] Game already started"));
		return;
	}

	bGameStarted = true;

	UE_LOG(LogTemp, Warning, TEXT("[GameMode] Loading game from slot: %s"), *SaveSlot);

	// Skip intro for loaded games
	// Load game state
	// Transition to main game level
	UGameplayStatics::OpenLevel(GetWorld(), FName(*MainGameLevelName));
}

void AR3ALN3TGameMode::SpawnIntroSequence()
{
	if (!IntroSequenceClass)
	{
		UE_LOG(LogTemp, Error, TEXT("[GameMode] IntroSequenceClass not set!"));
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	CurrentIntroSequence = GetWorld()->SpawnActor<AIntroSequence>(
		IntroSequenceClass,
		FVector::ZeroVector,
		FRotator::ZeroRotator,
		SpawnParams
	);

	if (CurrentIntroSequence)
	{
		// Bind completion event
		CurrentIntroSequence->OnIntroComplete.AddDynamic(this, &AR3ALN3TGameMode::OnIntroComplete);

		// Start intro
		CurrentIntroSequence->StartIntro();
	}
}

void AR3ALN3TGameMode::OnIntroComplete()
{
	UE_LOG(LogTemp, Warning, TEXT("[GameMode] Intro sequence complete"));

	// Transition to main game or character creation
	if (CharacterCreationWidgetClass)
	{
		// Show character creation UI
		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		if (PC)
		{
			UUserWidget* CharCreationWidget = CreateWidget<UUserWidget>(PC, CharacterCreationWidgetClass);
			if (CharCreationWidget)
			{
				CharCreationWidget->AddToViewport();
				PC->bShowMouseCursor = true;
				PC->SetInputMode(FInputModeGameAndUI());
			}
		}
	}
	else
	{
		// Load main game level directly
		UGameplayStatics::OpenLevel(GetWorld(), FName(*MainGameLevelName));
	}

	// Clean up intro sequence
	if (CurrentIntroSequence)
	{
		CurrentIntroSequence->Destroy();
		CurrentIntroSequence = nullptr;
	}
}

// IntroSequence.cpp
#include "IntroSequence.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Blueprint/UserWidget.h"

AIntroSequence::AIntroSequence()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.016f; // 60 FPS

	bIsPlaying = false;
	bSkipRequested = false;
	CurrentPhase = EIntroPhase::PHASE_NONE;
	PhaseStartTime = 0.0f;
	TotalIntroTime = SystemBootDuration + NeuralLoadDuration + CinematicDuration + 
	                 StoryRevealDuration + CharacterSelectDuration + FadeOutDuration;
}

void AIntroSequence::BeginPlay()
{
	Super::BeginPlay();

	// Setup player controller
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		PC->bShowMouseCursor = false;
		PC->SetInputMode(FInputModeGameOnly());
	}

	// Create canvas render target for UI
	if (!IntroCanvasRT)
	{
		IntroCanvasRT = UKismetRenderingLibrary::CreateRenderTarget2D(
			GetWorld(),
			static_cast<int32>(CinematicResolution.X),
			static_cast<int32>(CinematicResolution.Y),
			RTF_RGBA8
		);
	}
}

void AIntroSequence::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsPlaying)
	{
		return;
	}

	UpdateIntroPhase(DeltaTime);
}

void AIntroSequence::StartIntro()
{
	bIsPlaying = true;
	bSkipRequested = false;
	CurrentPhase = EIntroPhase::PHASE_SYSTEM_BOOT;
	PhaseStartTime = GetWorld()->GetTimeSeconds();

	// Setup player input
	SetupPlayerInputComponent(GetWorld()->GetFirstPlayerController()->InputComponent);

	// Start first phase
	SetupPhase(EIntroPhase::PHASE_SYSTEM_BOOT);
}

void AIntroSequence::SkipIntro()
{
	if (bAllowSkip)
	{
		bSkipRequested = true;
		bIsPlaying = false;
		TransitionToMainGame();
	}
}

void AIntroSequence::UpdateIntroPhase(float DeltaTime)
{
	float ElapsedTime = GetWorld()->GetTimeSeconds() - PhaseStartTime;
	float PhaseAlpha = GetPhaseAlpha();

	// Update current phase
	switch (CurrentPhase)
	{
		case EIntroPhase::PHASE_SYSTEM_BOOT:
			if (ElapsedTime >= SystemBootDuration)
			{
				CurrentPhase = EIntroPhase::PHASE_NEURAL_LOAD;
				PhaseStartTime = GetWorld()->GetTimeSeconds();
				SetupPhase(CurrentPhase);
			}
			break;

		case EIntroPhase::PHASE_NEURAL_LOAD:
			if (ElapsedTime >= NeuralLoadDuration)
			{
				CurrentPhase = EIntroPhase::PHASE_BLENDER_CINEMATIC;
				PhaseStartTime = GetWorld()->GetTimeSeconds();
				SetupPhase(CurrentPhase);
				SetupBlenderCinematic();
				PlayCinematicAudio();
			}
			break;

		case EIntroPhase::PHASE_BLENDER_CINEMATIC:
			if (ElapsedTime >= CinematicDuration)
			{
				CurrentPhase = EIntroPhase::PHASE_STORY_REVEAL;
				PhaseStartTime = GetWorld()->GetTimeSeconds();
				SetupPhase(CurrentPhase);
				StopCinematicAudio();
			}
			break;

		case EIntroPhase::PHASE_STORY_REVEAL:
			if (ElapsedTime >= StoryRevealDuration)
			{
				CurrentPhase = EIntroPhase::PHASE_CHARACTER_SELECT;
				PhaseStartTime = GetWorld()->GetTimeSeconds();
				SetupPhase(CurrentPhase);
			}
			break;

		case EIntroPhase::PHASE_CHARACTER_SELECT:
			if (ElapsedTime >= CharacterSelectDuration)
			{
				CurrentPhase = EIntroPhase::PHASE_FADE_OUT;
				PhaseStartTime = GetWorld()->GetTimeSeconds();
				SetupPhase(CurrentPhase);
			}
			break;

		case EIntroPhase::PHASE_FADE_OUT:
			if (ElapsedTime >= FadeOutDuration)
			{
				CurrentPhase = EIntroPhase::PHASE_COMPLETE;
				bIsPlaying = false;
				TransitionToMainGame();
			}
			break;

		case EIntroPhase::PHASE_COMPLETE:
			OnIntroComplete();
			break;

		default:
			break;
	}

	// Draw UI overlay
	if (IntroCanvasRT)
	{
		FCanvas Canvas(IntroCanvasRT->GameThread_GetRenderTargetResource(), nullptr);
		DrawIntroUI(&Canvas);
		Canvas.Flush_GameThread();
	}
}

void AIntroSequence::SetupPhase(EIntroPhase NewPhase)
{
	CurrentPhase = NewPhase;
	PhaseStartTime = GetWorld()->GetTimeSeconds();

	switch (NewPhase)
	{
		case EIntroPhase::PHASE_SYSTEM_BOOT:
			UE_LOG(LogTemp, Warning, TEXT("[INTRO] Phase: SYSTEM_BOOT"));
			break;

		case EIntroPhase::PHASE_NEURAL_LOAD:
			UE_LOG(LogTemp, Warning, TEXT("[INTRO] Phase: NEURAL_LOAD"));
			break;

		case EIntroPhase::PHASE_BLENDER_CINEMATIC:
			UE_LOG(LogTemp, Warning, TEXT("[INTRO] Phase: BLENDER_CINEMATIC"));
			break;

		case EIntroPhase::PHASE_STORY_REVEAL:
			UE_LOG(LogTemp, Warning, TEXT("[INTRO] Phase: STORY_REVEAL"));
			break;

		case EIntroPhase::PHASE_CHARACTER_SELECT:
			UE_LOG(LogTemp, Warning, TEXT("[INTRO] Phase: CHARACTER_SELECT"));
			break;

		case EIntroPhase::PHASE_FADE_OUT:
			UE_LOG(LogTemp, Warning, TEXT("[INTRO] Phase: FADE_OUT"));
			break;

		default:
			break;
	}
}

void AIntroSequence::DrawIntroUI(FCanvas* Canvas)
{
	if (!Canvas) return;

	float PhaseAlpha = GetPhaseAlpha();

	switch (CurrentPhase)
	{
		case EIntroPhase::PHASE_SYSTEM_BOOT:
			DrawSystemBootUI(Canvas, PhaseAlpha);
			break;

		case EIntroPhase::PHASE_NEURAL_LOAD:
			DrawNeuralLoadUI(Canvas, PhaseAlpha);
			break;

		case EIntroPhase::PHASE_STORY_REVEAL:
			DrawStoryRevealUI(Canvas, PhaseAlpha);
			break;

		case EIntroPhase::PHASE_CHARACTER_SELECT:
			DrawCharacterSelectUI(Canvas, PhaseAlpha);
			break;

		case EIntroPhase::PHASE_FADE_OUT:
		{
			FLinearColor FadeColor = FLinearColor::Black;
			FadeColor.A = PhaseAlpha;
			Canvas->DrawTile(0, 0, Canvas->GetRenderTarget()->GetSizeX(), 
			                Canvas->GetRenderTarget()->GetSizeY(), 
			                0, 0, 1, 1, FadeColor);
		}
		break;

		default:
			break;
	}

	// Draw skip prompt
	if (bAllowSkip && CurrentPhase != EIntroPhase::PHASE_FADE_OUT)
	{
		FVector2D SkipPos(Canvas->GetRenderTarget()->GetSizeX() - 200, 20);
		Canvas->DrawShadowedString(SkipPos.X, SkipPos.Y, TEXT("[ SKIP > Press ESC ]"), 
		                           GEngine->GetSmallFont(), FLinearColor::Yellow);
	}
}

void AIntroSequence::DrawSystemBootUI(FCanvas* Canvas, float PhaseAlpha)
{
	if (!Canvas) return;

	FVector2D ScreenSize(Canvas->GetRenderTarget()->GetSizeX(), 
	                     Canvas->GetRenderTarget()->GetSizeY());
	FVector2D TextCenter = ScreenSize * 0.5f;

	// System boot text
	FLinearColor BootColor = FLinearColor(0.0f, 1.0f, 0.0f, PhaseAlpha);
	Canvas->DrawShadowedString(TextCenter.X - 150, TextCenter.Y - 40, TEXT("> SYSTEM BOOT SEQUENCE"), 
	                           GEngine->GetSmallFont(), BootColor);

	// Loading percentage
	float LoadPercent = (GetWorld()->GetTimeSeconds() - PhaseStartTime) / SystemBootDuration * 100.0f;
	FString LoadText = FString::Printf(TEXT("[ %d%% ]"), static_cast<int32>(LoadPercent));
	Canvas->DrawShadowedString(TextCenter.X - 50, TextCenter.Y + 20, *LoadText, 
	                           GEngine->GetSmallFont(), BootColor);
}

void AIntroSequence::DrawNeuralLoadUI(FCanvas* Canvas, float PhaseAlpha)
{
	if (!Canvas) return;

	FVector2D ScreenSize(Canvas->GetRenderTarget()->GetSizeX(), 
	                     Canvas->GetRenderTarget()->GetSizeY());
	FVector2D TextCenter = ScreenSize * 0.5f;

	FLinearColor NeuralColor = FLinearColor(0.0f, 1.0f, 0.5f, PhaseAlpha);
	Canvas->DrawShadowedString(TextCenter.X - 200, TextCenter.Y - 40, 
	                           TEXT("NEURAL NETWORK INITIALIZING..."), 
	                           GEngine->GetSmallFont(), NeuralColor);

	// Progress bar
	float ProgressWidth = ScreenSize.X * 0.4f;
	float ProgressHeight = 20.0f;
	FVector2D ProgressStart(TextCenter.X - ProgressWidth * 0.5f, TextCenter.Y + 20);

	// Background
	Canvas->DrawTile(ProgressStart.X, ProgressStart.Y, ProgressWidth, ProgressHeight, 
	                 0, 0, 1, 1, FLinearColor(0.1f, 0.1f, 0.1f, PhaseAlpha * 0.8f));

	// Progress fill
	float Progress = (GetWorld()->GetTimeSeconds() - PhaseStartTime) / NeuralLoadDuration;
	Canvas->DrawTile(ProgressStart.X + 2, ProgressStart.Y + 2, 
	                (ProgressWidth - 4) * FMath::Clamp(Progress, 0.0f, 1.0f), 
	                ProgressHeight - 4, 0, 0, 1, 1, NeuralColor);

	// Border
	Canvas->DrawTile(ProgressStart.X, ProgressStart.Y, ProgressWidth, ProgressHeight, 
	                0, 0, 1, 1, NeuralColor * 0.5f);
}

void AIntroSequence::DrawStoryRevealUI(FCanvas* Canvas, float PhaseAlpha)
{
	if (!Canvas) return;

	FVector2D ScreenSize(Canvas->GetRenderTarget()->GetSizeX(), 
	                     Canvas->GetRenderTarget()->GetSizeY());
	FVector2D TextCenter = ScreenSize * 0.5f;

	FLinearColor TextColor = FLinearColor(1.0f, 1.0f, 1.0f, PhaseAlpha);

	// Story title
	Canvas->DrawShadowedString(TextCenter.X - 150, TextCenter.Y - 100, TEXT("R3ALN3T.EXE"), 
	                           GEngine->GetMediumFont(), TextColor);

	// Story paragraphs
	FString StoryLine1 = TEXT("The digital frontier has collapsed.");
	FString StoryLine2 = TEXT("Corporate overlords battle for network supremacy,");
	FString StoryLine3 = TEXT("wielding NetP Constructs—sentient AI entities born from code, chaos, and control.");

	Canvas->DrawShadowedString(TextCenter.X - 200, TextCenter.Y - 20, *StoryLine1, 
	                           GEngine->GetSmallFont(), TextColor);
	Canvas->DrawShadowedString(TextCenter.X - 250, TextCenter.Y + 20, *StoryLine2, 
	                           GEngine->GetSmallFont(), TextColor);
	Canvas->DrawShadowedString(TextCenter.X - 280, TextCenter.Y + 60, *StoryLine3, 
	                           GEngine->GetSmallFont(), TextColor);

	// Awakening text
	FString AwakeText = TEXT("You are a newly awakened NetP entity...");
	Canvas->DrawShadowedString(TextCenter.X - 180, TextCenter.Y + 120, *AwakeText, 
	                           GEngine->GetSmallFont(), 
	                           FLinearColor(0.0f, 1.0f, 0.5f, PhaseAlpha * 0.8f));
}

void AIntroSequence::DrawCharacterSelectUI(FCanvas* Canvas, float PhaseAlpha)
{
	if (!Canvas) return;

	FVector2D ScreenSize(Canvas->GetRenderTarget()->GetSizeX(), 
	                     Canvas->GetRenderTarget()->GetSizeY());
	FVector2D TextCenter = ScreenSize * 0.5f;

	FLinearColor SelectColor = FLinearColor(1.0f, 1.0f, 0.0f, PhaseAlpha);
	Canvas->DrawShadowedString(TextCenter.X - 200, TextCenter.Y, 
	                           TEXT("[ CONSTRUCT PROFILE LOADING... ]"), 
	                           GEngine->GetSmallFont(), SelectColor);
}

float AIntroSequence::GetPhaseAlpha() const
{
	float ElapsedTime = GetWorld()->GetTimeSeconds() - PhaseStartTime;
	float PhaseDuration = 0.0f;

	switch (CurrentPhase)
	{
		case EIntroPhase::PHASE_SYSTEM_BOOT:
			PhaseDuration = SystemBootDuration;
			break;
		case EIntroPhase::PHASE_NEURAL_LOAD:
			PhaseDuration = NeuralLoadDuration;
			break;
		case EIntroPhase::PHASE_BLENDER_CINEMATIC:
			PhaseDuration = CinematicDuration;
			break;
		case EIntroPhase::PHASE_STORY_REVEAL:
			PhaseDuration = StoryRevealDuration;
			break;
		case EIntroPhase::PHASE_CHARACTER_SELECT:
			PhaseDuration = CharacterSelectDuration;
			break;
		case EIntroPhase::PHASE_FADE_OUT:
			PhaseDuration = FadeOutDuration;
			break;
		default:
			return 1.0f;
	}

	return FMath::Clamp(ElapsedTime / PhaseDuration, 0.0f, 1.0f);
}

void AIntroSequence::TransitionToMainGame()
{
	// Load main game level or show character creation
	// Example:
	// UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("MainGameLevel")));

	UE_LOG(LogTemp, Warning, TEXT("[INTRO] Intro complete - transitioning to main game"));
}

void AIntroSequence::SetupBlenderCinematic()
{
	// Load and play Blender-exported video
	// Expected asset: /Game/Cinematics/IntrocinematicSequence.mp4 or Sequencer
	if (CinematicMediaPlayer)
	{
		// CinematicMediaPlayer->OpenUrl(TEXT("IntrocinematicSequence.mp4"));
		// CinematicMediaPlayer->Play();
	}

	UE_LOG(LogTemp, Warning, TEXT("[INTRO] Blender cinematic setup complete"));
}

void AIntroSequence::PlayCinematicAudio()
{
	if (!bPlayCinematicAudio) return;

	// Play intro audio track
	// Example:
	// UGameplayStatics::PlaySound2D(GetWorld(), IntroAudioAsset);

	UE_LOG(LogTemp, Warning, TEXT("[INTRO] Playing cinematic audio"));
}

void AIntroSequence::StopCinematicAudio()
{
	UE_LOG(LogTemp, Warning, TEXT("[INTRO] Stopping cinematic audio"));
}

void AIntroSequence::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (!PlayerInputComponent) return;

	// Skip intro with ESC
	PlayerInputComponent->BindAction("UI_Cancel", IE_Pressed, this, &AIntroSequence::SkipIntro);
}

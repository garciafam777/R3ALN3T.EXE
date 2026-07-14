// IntroSequence.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "Engine/Canvas.h"
#include "IntroSequence.generated.h"

/**
 * Intro sequence actor for R3ALN3T.EXE new game
 * Plays after player selects "New Game"
 * Combines Blender-designed cinematics with UI overlays
 */
UCLASS()
class R3ALN3TEXE_API AIntroSequence : public AActor
{
	GENERATED_BODY()

public:
	AIntroSequence();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Called from game mode to start intro
	UFUNCTION(BlueprintCallable, Category = "Intro")
	void StartIntro();

	// Skip intro and go to main game
	UFUNCTION(BlueprintCallable, Category = "Intro")
	void SkipIntro();

	// Called when intro completes
	UFUNCTION(BlueprintImplementableEvent, Category = "Intro")
	void OnIntroComplete();

protected:
	// Intro phases (each has specific timing and visuals)
	enum class EIntroPhase : uint8
	{
		PHASE_NONE = 0,
		PHASE_SYSTEM_BOOT = 1,      // 0-2s: System boot text
		PHASE_NEURAL_LOAD = 2,      // 2-4s: Neural network loading
		PHASE_BLENDER_CINEMATIC = 3, // 4-10s: Blender video sequence
		PHASE_STORY_REVEAL = 4,     // 10-14s: Story text overlay
		PHASE_CHARACTER_SELECT = 5, // 14-16s: Character creation prompt
		PHASE_FADE_OUT = 6,         // 16-18s: Fade to main game
		PHASE_COMPLETE = 7          // Complete
	};

	EIntroPhase CurrentPhase;
	float PhaseStartTime;
	float TotalIntroTime;

	// Camera for intro cinematic
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intro|Camera")
	class ACameraActor* IntroCameraActor;

	// Media/Video components for Blender cinematic
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intro|Media")
	class UMediaPlayer* CinematicMediaPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intro|Media")
	class UMediaTexture* CinematicMediaTexture;

	// Asset references to Blender imports
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intro|Assets")
	class UStaticMesh* NetPConstructMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intro|Assets")
	class USkeletalMesh* HologramMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intro|Assets")
	class UMaterial* HologramMaterial;

	// UI Canvas for overlay text
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intro|UI")
	class UCanvasRenderTarget2D* IntroCanvasRT;

	// Timing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intro|Timing")
	float SystemBootDuration = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intro|Timing")
	float NeuralLoadDuration = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intro|Timing")
	float CinematicDuration = 6.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intro|Timing")
	float StoryRevealDuration = 4.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intro|Timing")
	float CharacterSelectDuration = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intro|Timing")
	float FadeOutDuration = 2.0f;

	// Settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intro|Settings")
	bool bAllowSkip = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intro|Settings")
	bool bPlayCinematicAudio = true;

	// Internal state
	bool bIsPlaying;
	bool bSkipRequested;
	FVector2D CinematicResolution = FVector2D(1920, 1080);

	// Phase management
	void UpdateIntroPhase(float DeltaTime);
	void SetupPhase(EIntroPhase NewPhase);
	void DrawIntroUI(class FCanvas* Canvas);
	void DrawSystemBootUI(class FCanvas* Canvas, float PhaseAlpha);
	void DrawNeuralLoadUI(class FCanvas* Canvas, float PhaseAlpha);
	void DrawStoryRevealUI(class FCanvas* Canvas, float PhaseAlpha);
	void DrawCharacterSelectUI(class FCanvas* Canvas, float PhaseAlpha);

	// Helper functions
	float GetPhaseAlpha() const;
	void TransitionToMainGame();
	void SetupBlenderCinematic();
	void PlayCinematicAudio();
	void StopCinematicAudio();

public:
	// Input handling
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};

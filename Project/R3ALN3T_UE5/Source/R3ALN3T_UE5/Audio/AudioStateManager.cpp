// AudioStateManager.cpp — Chapter 7.2 dynamic soundtrack router.
#include "AudioStateManager.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundWave.h"
#include "Components/AudioComponent.h"      // UAudioComponent (crossfade)
#include "../Gameplay/Battle/R3ALN3T_BattleManager.h"

void UAudioStateManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// Wire battle lifecycle -> music crossfade.
	if (UR3ALN3T_BattleManager* BM = GetGameInstance()->GetSubsystem<UR3ALN3T_BattleManager>())
	{
		BM->OnBattleStart.AddDynamic(this, &UAudioStateManager::HandleBattleBegin);
		BM->OnBattleEnd.AddDynamic(this, &UAudioStateManager::HandleBattleEnd);
		bAudioBound = true;
	}

	// Start in Exploration (overworld ambient) once a world is ready.
	if (UWorld* World = GetGameInstance()->GetWorld())
	{
		SetMusicCategory(EMusicCategory::Exploration);
	}
}

void UAudioStateManager::Deinitialize()
{
	if (ActiveComp) { ActiveComp->Stop(); }
	if (FadingComp) { FadingComp->Stop(); }
	ActiveComp = nullptr;
	FadingComp = nullptr;
	Super::Deinitialize();
}

bool UAudioStateManager::ResolveTrack(EMusicCategory Category,
	TSoftObjectPtr<USoundWave>& OutWave, float& OutVolume, float& OutFade) const
{
	if (!MusicTable) return false;
	static const FString Ctx(TEXT("AudioStateManager"));
	for (const FName RowName : MusicTable->GetRowNames())
	{
		const FMusicTrackRow* Row = MusicTable->FindRow<FMusicTrackRow>(RowName, Ctx);
		if (Row && Row->Category == Category)
		{
			OutWave = Row->SoundWave;
			OutVolume = Row->VolumeScale;
			OutFade = Row->CrossfadeDuration;
			return true;
		}
	}
	return false;
}

void UAudioStateManager::SetMusicCategory(EMusicCategory NewCategory)
{
	if (NewCategory == CurrentCategory && ActiveComp && ActiveComp->IsPlaying())
	{
		return; // already playing this category
	}
	CurrentCategory = NewCategory;

	TSoftObjectPtr<USoundWave> Wave;
	float Volume = 1.f, Fade = 2.f;
	if (!ResolveTrack(NewCategory, Wave, Volume, Fade))
	{
		UE_LOG(LogTemp, Warning, TEXT("[Audio] No track for category %d in DT_Music; skipping."),
			static_cast<int32>(NewCategory));
		return;
	}

	USoundWave* Sound = Wave.LoadSynchronous();
	if (!Sound) return;

	UWorld* World = GetGameInstance()->GetWorld();
	if (!World) return;

	// Demote the active component to "fading" and spin up a new one.
	if (ActiveComp)
	{
		FadingComp = ActiveComp;
		FadingComp->FadeOut(Fade, 0.f);
		// Self-clean: when fade completes, stop + clear.
		FTimerHandle _; // anonymous; FadingComp cleared on next switch
	}
	ActiveComp = UGameplayStatics::SpawnSound2D(World, Sound, Volume);
}

void UAudioStateManager::HandleBattleBegin()
{
	SetMusicCategory(EMusicCategory::Battle);
}

void UAudioStateManager::HandleBattleEnd(FBattleResult Result)
{
	SetMusicCategory(EMusicCategory::Exploration);
}

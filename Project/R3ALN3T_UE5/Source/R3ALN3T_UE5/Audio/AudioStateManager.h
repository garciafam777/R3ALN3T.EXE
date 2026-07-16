// AudioStateManager.h — Chapter 7.2 dynamic soundtrack router.
// Game-instance subsystem that crossfades music by EMusicCategory (Exploration <-> Battle,
// etc.) in response to battle lifecycle events. Reads the canonical FMusicTrackRow table
// (DT_Music) so tracks are data-driven, not hardcoded. KISS: two audio components, one
// active, one fading.
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Engine/DataTable.h"
#include "AudioTypes.h"
#include "AudioStateManager.generated.h"

UCLASS()
class R3ALN3T_UE5_API UAudioStateManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// Switch the active music category. Crossfades from the current track to the new
	// one over the DataTable's CrossfadeDuration. No-op if the category is unchanged.
	UFUNCTION(BlueprintCallable, Category = "Audio")
	void SetMusicCategory(EMusicCategory NewCategory);

	EMusicCategory GetCurrentCategory() const { return CurrentCategory; }

	// DataTable of FMusicTrackRow (DT_Music). Assign via DefaultGame.ini or editor.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	UDataTable* MusicTable = nullptr;

protected:
	// Resolve a category to its row's SoundWave + crossfade settings from MusicTable.
	bool ResolveTrack(EMusicCategory Category, TSoftObjectPtr<USoundWave>& OutWave,
	                  float& OutVolume, float& OutFade) const;

	// Battle lifecycle hooks (wired in Initialize).
	UFUNCTION()
	void HandleBattleBegin();
	UFUNCTION()
	void HandleBattleEnd(FBattleResult Result);

private:
	UPROPERTY()
	UAudioComponent* ActiveComp = nullptr;

	UPROPERTY()
	UAudioComponent* FadingComp = nullptr;

	EMusicCategory CurrentCategory = EMusicCategory::Exploration;
	bool bAudioBound = false;
};

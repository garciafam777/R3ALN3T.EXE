# Step8_Dynamic_Audio_Pipeline.md
## Dynamic Audio Pipeline (MetaSounds)

Maps 69 audio files from C:\Users\richa\Desktop\R3ALN3T_UE5\Content\R3ALN3T\Audio. 
Tracks with () map to Battle arrays. Remaining map to Exploration arrays.

#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "R3ALN3T_AudioStructures.generated.h"

USTRUCT(BlueprintType)
struct FMusicTrackRow : public FTableRowBase
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName TrackID;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bIsBattleTrack;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TSoftObjectPtr<USoundWave> AudioAsset;
};

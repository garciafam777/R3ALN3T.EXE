#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AudioTypes.generated.h"

UENUM(BlueprintType)
enum class EMusicCategory : uint8
{
    Exploration  UMETA(DisplayName = "Exploration / Ambient"),
    Battle       UMETA(DisplayName = "Battle"),
    Theme        UMETA(DisplayName = "Character / Zone Theme"),
    Cinematic    UMETA(DisplayName = "Cinematic / Cutscene"),
    UI           UMETA(DisplayName = "Menu / UI")
};

UENUM(BlueprintType)
enum class EAudioLayer : uint8
{
    None         UMETA(DisplayName = "Unspecified / Global"),
    Heaven       UMETA(DisplayName = "Heaven"),
    OuterSpace   UMETA(DisplayName = "Outer Space"),
    LunaMars     UMETA(DisplayName = "Luna / Mars"),
    Reality      UMETA(DisplayName = "R3AL World"),
    Cyberspace   UMETA(DisplayName = "Cyberspace Mirror"),
    Hell         UMETA(DisplayName = "Hell")
};

USTRUCT(BlueprintType)
struct FMusicTrackRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    FName TrackID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    EMusicCategory Category = EMusicCategory::Exploration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    EAudioLayer Layer = EAudioLayer::None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    TSoftObjectPtr<USoundWave> SoundWave;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    float VolumeScale = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    float CrossfadeDuration = 2.0f;
};

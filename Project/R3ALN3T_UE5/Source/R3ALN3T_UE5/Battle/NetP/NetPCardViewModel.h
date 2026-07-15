// NetPCardViewModel.h — Decoupled resolver for WBP_NetPCard framing.
// Reads the FrameByElement DataTable (live schema: element, frameTexture, frameName)
// via an EXPLICIT EElement -> RowName map. No ordinal math, so inserting an enum
// value in the middle can never shift a lookup. No UMG deps in this header.
#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "../../Core/Types/TrinityMatrixTypes.h"
#include "NetPCardViewModel.generated.h"

// Result of a frame resolution — pure data, safe to hand to any presenter.
USTRUCT(BlueprintType)
struct FNetPCardFrame
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "R3ALN3T|NetP")
    TSoftObjectPtr<UTexture2D> FrameTexture;

    UPROPERTY(BlueprintReadOnly, Category = "R3ALN3T|NetP")
    FString FrameName;

    UPROPERTY(BlueprintReadOnly, Category = "R3ALN3T|NetP")
    EElement ResolvedElement = EElement::None;

    UPROPERTY(BlueprintReadOnly, Category = "R3ALN3T|NetP")
    bool bFound = false;
};

UCLASS()
class R3ALN3T_UE5_API UNetPCardViewModel : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    // Explicit, drift-safe map of EElement -> FrameByElement row name.
    // Row names are Row01..Row21 (the DataTable is keyed by RowNN, NOT by element
    // name — the prior name-keyed lookup in SetNetP was a latent bug; this map is
    // the fix). Row06 stores element=None mapped to holy_frame (intentional schema
    // anomaly, self-documented here).
    // EElement::Light has NO FrameByElement row (data gap, open item) — omitted on
    // purpose so GetElementRowMap().Find(Light) returns null and we warn, never crash.
    static const TMap<EElement, FName>& GetElementRowMap();

    // Resolve a NetP element to its card frame. Returns false (with a logged warning,
    // never a crash) if the element has no row or the table is missing.
    UFUNCTION(BlueprintCallable, Category = "R3ALN3T|NetP")
    static bool ResolveNetPCardFrame(EElement Element, UDataTable* FrameTable, FNetPCardFrame& OutFrame);
};

// NetPCardWidget.h — G3: binds a NetP's canon-21 element to its card frame texture.
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "../../Core/Types/TrinityMatrixTypes.h"
#include "NetPCardWidget.generated.h"

// Row struct for the FrameByElement DataTable (imported from FrameByElement.csv).
USTRUCT(BlueprintType)
struct FFrameByElementRow : public FTableRowBase
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) EElement Element = EElement::None;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TSoftObjectPtr<UTexture2D> FrameTexture;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString FrameName;
};

UCLASS()
class R3ALN3T_UE5_API UNetPCardWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    // G3: given a NetP, show its element's frame. Looks up FrameByElement DataTable by NetP.Element.
    UFUNCTION(BlueprintCallable, Category = "R3ALN3T|NetP")
    void SetNetP(const FR3ALN3TNetPStatus& NetP);

    // Assign in editor (Details) — path to the imported FrameByElement DataTable.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "R3ALN3T|NetP")
    TSoftObjectPtr<UDataTable> FrameByElementTable;

    // The frame image on the widget (BindWidget in Blueprint).
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    TObjectPtr<class UImage> FrameImage = nullptr;
};

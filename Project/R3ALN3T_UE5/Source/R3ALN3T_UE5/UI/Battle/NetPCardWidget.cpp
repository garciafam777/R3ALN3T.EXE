// NetPCardWidget.cpp — G3 implementation.
#include "NetPCardWidget.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"

void UNetPCardWidget::SetNetP(const FR3ALN3TNetPStatus& NetP)
{
    if (!FrameImage) return;

    UDataTable* Table = FrameByElementTable.LoadSynchronous();
    if (!Table) return;

    // Key the row by the EElement name (FrameByElement.csv uses EElement enum names).
    const FString Key = StaticEnum<EElement>()->GetNameStringByValue(static_cast<int64>(NetP.Element));
    const FFrameByElementRow* Row = Table->FindRow<FFrameByElementRow>(*Key, TEXT("FrameByElement"));
    if (!Row) return;

    UTexture2D* Tex = Row->FrameTexture.LoadSynchronous();
    if (Tex)
    {
        FrameImage->SetBrushFromTexture(Tex);
    }
}

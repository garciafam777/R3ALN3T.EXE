// NetPCardWidget.cpp — G3 implementation (drift-safe via NetPCardViewModel).
#include "NetPCardWidget.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "../../Battle/NetP/NetPCardViewModel.h"

void UNetPCardWidget::SetNetP(const FR3ALN3TNetPStatus& NetP)
{
    if (!FrameImage) return;

    UDataTable* Table = FrameByElementTable.LoadSynchronous();
    if (!Table) return;

    // Resolve the card frame through the explicit EElement->RowName map.
    FNetPCardFrame Frame;
    if (!UNetPCardViewModel::ResolveNetPCardFrame(NetP.Element, Table, Frame))
    {
        FrameImage->SetBrushFromTexture(nullptr); // graceful blank; texture gen is open item #4
        return;
    }

    UTexture2D* Tex = Frame.FrameTexture.LoadSynchronous();
    if (Tex)
    {
        FrameImage->SetBrushFromTexture(Tex);
    }
    else
    {
        // Texture asset not generated yet (open item #4) — blank, never crash.
        UE_LOG(LogTemp, Warning, TEXT("[NetPCard] Missing texture for %s (%s); defaulting to blank."),
            *Frame.FrameName, *Frame.FrameTexture.ToString());
        FrameImage->SetBrushFromTexture(nullptr);
    }
}

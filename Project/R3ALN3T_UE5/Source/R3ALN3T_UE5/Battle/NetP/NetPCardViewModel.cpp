// NetPCardViewModel.cpp — explicit EElement->RowName resolution off FrameByElement.
#include "NetPCardViewModel.h"
#include "../../UI/Battle/NetPCardWidget.h" // for FFrameByElementRow (row struct lives with the widget)

const TMap<EElement, FName>& UNetPCardViewModel::GetElementRowMap()
{
    static const TMap<EElement, FName> Map =
    {
        { EElement::None,     FName(TEXT("Row06")) }, // None -> holy_frame (schema anomaly, intentional)
        { EElement::Fire,     FName(TEXT("Row01")) },
        { EElement::Aqua,     FName(TEXT("Row02")) },
        { EElement::Elec,     FName(TEXT("Row03")) },
        { EElement::Wood,     FName(TEXT("Row04")) },
        { EElement::Wind,     FName(TEXT("Row05")) },
        { EElement::Earth,    FName(TEXT("Row12")) },
        // EElement::Light -> NO ROW (FrameByElement lacks a Light frame; data gap)
        { EElement::Dark,     FName(TEXT("Row11")) },
        { EElement::Null,     FName(TEXT("Row17")) },
        { EElement::Glitch,   FName(TEXT("Row13")) },
        { EElement::Plasma,   FName(TEXT("Row18")) },
        { EElement::Crystal,  FName(TEXT("Row10")) },
        { EElement::Time,     FName(TEXT("Row21")) },
        { EElement::Gravity,  FName(TEXT("Row14")) },
        { EElement::Sound,    FName(TEXT("Row20")) },
        { EElement::Metal,    FName(TEXT("Row15")) },
        { EElement::Poison,   FName(TEXT("Row19")) },
        { EElement::Nature,   FName(TEXT("Row16")) },
        { EElement::Ice,      FName(TEXT("Row08")) },
        { EElement::Blood,    FName(TEXT("Row09")) },
        { EElement::Void,     FName(TEXT("Row07")) },
    };
    return Map;
}

bool UNetPCardViewModel::ResolveNetPCardFrame(EElement Element, UDataTable* FrameTable, FNetPCardFrame& OutFrame)
{
    OutFrame = FNetPCardFrame{};

    if (!FrameTable)
    {
        UE_LOG(LogTemp, Error, TEXT("[NetPCard] FrameTable is NULL!"));
        return false;
    }

    const FName* RowNamePtr = GetElementRowMap().Find(Element);
    if (!RowNamePtr)
    {
        UE_LOG(LogTemp, Warning, TEXT("[NetPCard] EElement '%s' has no FrameByElement row (data gap)."),
            *UEnum::GetValueAsString(Element));
        return false;
    }

    const FFrameByElementRow* Row = FrameTable->FindRow<FFrameByElementRow>(*RowNamePtr, TEXT("NetPCard"));
    if (!Row)
    {
        UE_LOG(LogTemp, Warning, TEXT("[NetPCard] Row '%s' missing in FrameByElement DataTable!"), *RowNamePtr->ToString());
        return false;
    }

    // Schema integrity: the row's element must equal the requested element.
    // Row06 stores element=None, which equals EElement::None, so this holds
    // uniformly — no None special-case required.
    ensureMsgf(Row->Element == Element,
        TEXT("FrameByElement schema mismatch: row %s element=%s expected=%s"),
        *RowNamePtr->ToString(), *UEnum::GetValueAsString(Row->Element), *UEnum::GetValueAsString(Element));

    OutFrame.ResolvedElement = Row->Element;
    OutFrame.FrameTexture = Row->FrameTexture;
    OutFrame.FrameName = Row->FrameName;
    OutFrame.bFound = true;
    return true;
}

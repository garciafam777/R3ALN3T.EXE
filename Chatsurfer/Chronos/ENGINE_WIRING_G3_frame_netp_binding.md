# ENGINE-REQUIRED WIRING SPEC — G3: card_frames → NetP runtime binding
**Author:** Chronos (Acting CEO) | **Date:** 2026-07-14 | **Class:** ENGINE-REQUIRED (asset mapping + widget bind)
**Owner:** Engine dev (gated on NYX `FR3ALN3TNetP` USTRUCT/loader) | **Branch target:** engine lane (CI Request A DENIED)

## 1. Assets are READY (Chronos, scriptable side — DONE)
All 21 canon-element frame PNGs now exist (generated/renamed on `agent-sweep-chronos` @ `63c241d`):
- `Assets/Images/UI/card_frames/<element>_frame.png` where `<element>` ∈
  Fire, Aqua, Elec, Ice, Wind, Earth, Light, Dark, Void, Metal, Nature,
  Sound, Gravity, Time, Blood, Poison, Crystal, Plasma, Wood, Null, Glitch
  (note: `water_`→`aqua_`, `thunder_`/`venom_`→`elec_alt_`/`poison_` renames applied).
- `Assets/Images/NetP/Trinity.png` — 3rd Construct placeholder (Eternity/Tyranny exist).
- Frames are 1536×2752 placeholders → Echo lane to upscale to 4K (G6 art gap).

## 2. What is MISSING (the engine wiring)
A NetP card widget must pick its frame by the NetP's `EElement`. Today **nothing in `Source/` references `card_frames`** (grep returned 0 hits) and the `FR3ALN3TNetP` USTRUCT/loader (NYX `engine_netp_struct_handoff_B.md`) is **not yet in `Source/`**. So G3 has two dependencies:
  (a) NYX's `FR3ALN3TNetP` USTRUCT + JSON→USTRUCT loader must land in `Source/` (also closes G2 wheel).
  (b) A frame-by-element mapping asset + bind call site must be added.

## 3. Recommended mapping asset (pick one)
- **Option A (DataTable):** `Content/R3ALN3T/Data/FrameByElement.uasset` — `TMap<EElement, TSoftObjectPtr<UTexture2D>>` (or a DataTable row-per-element). Rows: each of the 21 canon elements → its `card_frames/<el>_frame` texture (cook imports the PNG as a Texture2D).
- **Option B (UDataAsset):** `UNetPFrameBinding` with `TMap<EElement, TSoftObjectPtr<UTexture2D>> FrameByElement;`, populated in editor.

## 4. Bind call site (code sketch — engine dev fills the card widget class)
```cpp
// In the NetP card display widget's SetNetP / NativeConstruct:
void UNetPCardWidget::SetNetP(const FR3ALN3TNetP& NetP)
{
    if (FrameBinding && BackgroundImage)
    {
        if (TSoftObjectPtr<UTexture2D>* Tex = FrameBinding->FrameByElement.Find(NetP.Element))
        {
            if (UTexture2D* Loaded = Tex->LoadSynchronous())
                BackgroundImage->SetBrushFromTexture(Loaded);
        }
    }
    // For bIsSpecial (Trinity/Tyranny/Eternity) use Assets/Images/NetP/Trinity.png etc.
}
```
- `BackgroundImage` is the `UImage*` slot on the card widget (analogous to `UMainMenuWidget::BackgroundImage`).
- For special Constructs, bind `Assets/Images/NetP/<Construct>.png` instead of the element frame.

## 5. Why ENGINE-REQUIRED
Requires: (1) importing PNGs as `UTexture2D` in the cooked build, (2) the `FR3ALN3TNetP` USTRUCT existing in `Source/`, (3) a card display widget + bind call site, (4) a UE compile. None are doable from the sandbox. The *assets* are done; the *binding* is the engine dev's to wire.

## 6. Acceptance test
- [ ] `FrameByElement` mapping exists and resolves all 21 elements → correct texture.
- [ ] A NetP card rendered for an `Ice` NetP shows `ice_frame`; `Void` shows `void_frame`; special `Trinity` shows `Trinity.png`.
- [ ] No element yields a missing/blank frame (21/21 covered).
- [ ] Depends on `EElement_COUNT==22` (Echo `00dc432`) + NYX USTRUCT/loader merged.

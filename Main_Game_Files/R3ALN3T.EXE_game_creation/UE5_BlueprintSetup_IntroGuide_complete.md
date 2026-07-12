# R3ALN3T.EXE Intro - UE5 Blueprint Setup Guide

## Overview
This guide walks through setting up the intro sequence in UE5 using Blueprints and C++.

## Step 1: Create the Intro Level

### 1.1 New Level
1. File → New Level → Default
2. Name it: `L_Intro`
3. Save in `/Content/Levels/Intro/`

### 1.2 Set Up Basic Scene
1. Delete default actors (Directional Light, Sky Atmosphere, etc. if you prefer a dark intro)
2. Add new actor: **Plane**
   - Location: (0, 0, 0)
   - Scale: (10, 5.625, 1) — 16:9 aspect ratio
   - Material: Assign video playback material (see Step 2)

---

## Step 2: Create Video Playback Material

### 2.1 Create Material
1. **Content Browser** → Right-click → Material → `M_IntroVideo`
2. In Material Editor:
   ```
   Main Material Layer:
   - Base Color: CONNECTED to Media Texture Sample
   - Emission: CONNECTED to Media Texture Sample (for glow)
   - Emission Strength: 1.0
   - Metallic: 0.0
   - Roughness: 0.5
   ```

3. Drag the imported `Intro_Video` Media Texture into the graph
4. Sample it and connect to Base Color
5. Connect same texture sample to Emission

### 2.2 Compile & Save
- Click **Compile** and **Save**

---

## Step 3: Set Up Game Mode

### 3.1 Create Blueprint from C++ Class
1. **Content Browser** → Right-click → Blueprint Class
2. Parent Class: `R3ALN3TGameMode`
3. Name: `BP_R3ALN3TGameMode`
4. Open Blueprint:
   ```
   Details Panel:
   - Intro Sequence Class: Select IntroSequence (C++ class or Blueprint)
   - Main Game Level Name: "MainGame" (or your main level name)
   - Character Creation Widget Class: (optional - if you have one)
   ```

### 3.2 Set as Default Game Mode
1. **Edit** → **Project Settings** → **Maps & Modes**
2. Set **Default GameMode** → `BP_R3ALN3TGameMode`
3. Set **Default Player Start Class** → Default (or custom if needed)

---

## Step 4: Create the Intro Sequence Blueprint

### 4.1 Create Blueprint from C++ Class
1. **Content Browser** → Right-click → Blueprint Class
2. Parent Class: `AIntroSequence`
3. Name: `BP_IntroSequence`
4. Open Blueprint

### 4.2 Configure in Details
In the **Details Panel**, under **Intro** category:
```
[ CAMERA ]
Intro Camera Actor: (leave as None for now - auto-managed)

[ MEDIA ]
Cinematic Media Player: Select "Intro_Video" Media Player asset
Cinematic Media Texture: Select "Intro_Video_Texture" Media Texture asset

[ ASSETS ]
NetP Construct Mesh: NetPConstruct_SM (imported FBX)
Hologram Mesh: Hologram_SK (imported Skeletal Mesh)
Hologram Material: M_Hologram

[ TIMING ]
System Boot Duration: 2.0
Neural Load Duration: 2.0
Cinematic Duration: 6.0
Story Reveal Duration: 4.0
Character Select Duration: 2.0
Fade Out Duration: 2.0

[ SETTINGS ]
Allow Skip: true
Play Cinematic Audio: true
```

### 4.3 Add Event Handlers (Blueprint)
1. **Event Graph** → Right-click
2. Add Event: **Event On Intro Complete**
   - Node: **Open Level**
     - Level Name: "MainGame"
   - This automatically transitions to main game when intro finishes

---

## Step 5: Create Main Menu Level

### 5.1 New Level
1. File → New Level → Default
2. Name: `L_MainMenu`
3. Add UI Widget

### 5.2 Create Main Menu Widget
1. **Content Browser** → Right-click → User Interface → Widget Blueprint
2. Name: `W_MainMenu`
3. Open and add buttons:
   ```
   Layout (Vertical):
   - "NEW GAME" button
     - On Clicked: Call GameMode → StartNewGame()
   
   - "LOAD GAME" button
     - On Clicked: Show save slots dialog
   
   - "SETTINGS" button
   
   - "EXIT" button
     - On Clicked: Quit Game
   ```

### 5.3 Example Blueprint Code (Pseudo)
```
Event: On New Game Button Clicked
├─ Get Game Mode (Cast to R3ALN3TGameMode)
├─ Call StartNewGame
└─ Game Mode spawns IntroSequence

Game Mode → StartNewGame()
├─ Spawn BP_IntroSequence actor
└─ Call its StartIntro() function
```

---

## Step 6: Audio Integration

### 6.1 Create Sound Cue
1. **Content Browser** → Right-click → Sound Cue → `SC_IntroMusic`
2. Double-click to open
3. Drag **Intro_Audio** (SoundWave) into the Cue Editor
4. Connect to **Output**
5. Set Volume Multiplier: 0.8 (not too loud)
6. Save

### 6.2 Trigger in Intro Blueprint
In **BP_IntroSequence** Event Graph:
```
Event: On Phase Change (Phase == PHASE_BLENDER_CINEMATIC)
├─ Play Sound 2D
│  └─ Sound: SC_IntroMusic
│  └─ Volume Multiplier: 1.0
└─ Store reference for stop later
```

---

## Step 7: UI Overlay Setup

### 7.1 Create Intro UI Widget (Optional - For Text Overlays)
If you want animated text on top of the cinematic:

1. **Content Browser** → User Interface → Widget Blueprint
2. Name: `W_IntroOverlay`
3. Canvas layout with:
   ```
   - Vertical Box (Center)
     - Text: "R3ALN3T.EXE" (size 80, green color)
     - Text: Story paragraphs (size 20)
     - Text: "[ SKIP > ESC ]" (bottom right, size 14)
   ```

4. Add animations in Widget Designer:
   ```
   - Fade In (0-1s): Story title appears
   - Fade In (delay 1s): First paragraph
   - Fade In (delay 2s): Second paragraph
   ```

### 7.2 Display Widget During Intro
In **BP_IntroSequence**:
```
Event: Begin Play
├─ Create Widget: W_IntroOverlay
└─ Add to Viewport (Z-Order: 10)
```

---

## Step 8: Input Handling (Skip Button)

### 8.1 Set Up Input Action
1. **Project Settings** → **Input** → **Input Actions**
2. Add Input Action: `IA_UI_Cancel` (should already exist in UE5)
3. Map to **ESC** key

### 8.2 Bind in Intro Blueprint
Already handled in `IntroSequence.cpp` via:
```cpp
PlayerInputComponent->BindAction("UI_Cancel", IE_Pressed, this, &AIntroSequence::SkipIntro);
```

Test by pressing **ESC** during intro → Should skip to main game.

---

## Step 9: Placement in Level

### 9.1 Place Intro Sequence Actor
1. Open **L_Intro** level
2. **Place Actor** → Search for `BP_IntroSequence`
3. Click in viewport to place (location doesn't matter for actor)

### 9.2 Configure Transforms (if needed)
- Location: (0, 0, 0)
- Rotation: (0, 0, 0)
- Scale: (1, 1, 1)

---

## Step 10: Testing

### 10.1 Play in Editor
1. Click **Play** (or **ALT+P**)
2. Verify intro sequence starts automatically
3. Check:
   - [ ] System boot text displays
   - [ ] Video plays correctly
   - [ ] Audio plays in sync
   - [ ] Story text appears
   - [ ] ESC key skips to next phase
   - [ ] Auto-transitions to main game after fade-out

### 10.2 Packaged Build
1. **File** → **Package Project** → Select platform
2. After build completes, run `.exe`
3. Verify intro plays from start

---

## Advanced: Procedural Effects in UE5

### A.1 Add Glitch Post-Process
1. **Place Actor** → **Post Process Volume**
2. In Details:
   ```
   [ POST PROCESS ]
   - Bloom: Intensity 2.0
   - Motion Blur: Amount 0.5
   - Film Grain: Intensity 0.1
   ```

### A.2 Add Dynamic Lighting
1. **Place Actor** → **Point Light**
2. Properties:
   ```
   - Color: Cyan (#00FF00)
   - Intensity: 2000 lumens
   - Attenuation Radius: 5000 cm
   ```
3. Animate brightness in Blueprint:
   ```
   Timeline Node:
   - Float Curve: Intensity 0.5 → 2.0 → 0.5 (6 seconds)
   ├─ Connect to Light → Set Intensity
   ```

---

## Troubleshooting

| Issue | Solution |
|-------|----------|
| Video doesn't play | Check Media Player asset is assigned. Verify .mp4 format is supported. |
| Audio out of sync | Adjust timing in IntroSequence.cpp or media player start time. |
| Text is blurry | Increase widget scale or use higher resolution render target. |
| Skip button doesn't work | Verify input binding: Project Settings → Input → Check "UI_Cancel" exists. |
| Intro freezes | Check media file isn't corrupted. Try lower bitrate MP4. |
| Transition is jarring | Add fade-to-black layer at end (handled in PHASE_FADE_OUT). |

---

## Summary

You now have:
- ✅ **Intro Sequence Actor** (C++): Manages phases and timing
- ✅ **Game Mode** (C++): Spawns intro and handles game flow
- ✅ **Blender Assets**: Video, audio, 3D models
- ✅ **UI Layer**: Text overlays and skip button
- ✅ **Integration**: Fully playable from main menu to main game

**Next:** Customize visuals, adjust timing, and playtest extensively!

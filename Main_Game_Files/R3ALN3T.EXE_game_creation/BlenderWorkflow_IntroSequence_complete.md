# R3ALN3T.EXE - Intro Sequence Blender Workflow

## Overview
This guide explains how to create and export Blender assets for the R3ALN3T.EXE intro sequence to be used in Unreal Engine 5.

## Project Structure for Intro Assets

```
Main_Game_Files/R3ALN3T.EXE/
├── R3ALN3TEXE/
│   └── Content/
│       ├── Cinematics/
│       │   ├── Intro_Main/
│       │   │   ├── IntroSequence.blend (source)
│       │   │   ├── Intro_Video.mp4 (rendered)
│       │   │   ├── Intro_Audio.wav (audio track)
│       │   │   └── Textures/
│       │   │
│       │   └── Characters/
│       │       ├── NetPConstruct.blend
│       │       └── Hologram.blend
│       │
│       └── Materials/
│           ├── M_Hologram
│           ├── M_GlitchEffect
│           └── M_CyberpunkUI
```

## Part 1: Blender Scene Setup

### 1.1 Create Main Intro Cinematic Scene
**File:** `IntroSequence.blend`

**Scene Settings:**
- Resolution: 1920 x 1080 (Full HD)
- Frame Rate: 30 fps (match UE5 cinematic playback)
- Duration: 6 seconds (180 frames)
- Format: Render as H.264 MP4

**Scene Composition:**

#### Timeline Breakdown:
```
Frame 0-30 (0-1s):     System boot fade-in, title card appears
Frame 30-90 (1-3s):    Neural network visualization (animated grid/lines)
Frame 90-150 (3-5s):   NetP Construct awakens (model morphing)
Frame 150-180 (5-6s):  Transition/fade to white, ready for handoff to UE5
```

**Recommended Objects:**

1. **Title Card (planes with text)**
   - "R3ALN3T.EXE" centered, cyberpunk font
   - Green-on-black terminal aesthetic
   - Glow effect using Emission material

2. **Neural Network Visualization**
   - Grid of vertices/nodes
   - Animated connections drawing themselves
   - Use procedural Geometry Nodes for scalability

3. **NetP Construct Model**
   - 3D model with metallic/holographic appearance
   - Animated rotation and scaling
   - Morphing between different forms (optional complexity)

4. **Lighting**
   - Key light: Green (#00FF00 or #00AA00) from upper left
   - Fill light: Dim blue from upper right
   - Environment: Dark cyberpunk interior (HDRI)

5. **Camera Movement**
   - Static or slow dolly-zoom for dramatic effect
   - Keyframe Path: (0,0,-5) → (0,2,-8) over 6 seconds

### 1.2 Create NetP Construct Model
**File:** `NetPConstruct.blend`

**Purpose:** Static mesh for UE5 import (NOT for intro video)

**Specifications:**
- Polygons: 50k-200k (depends on detail level)
- Rig: None (static mesh)
- Materials: 2-4 slots (Metallic, Holographic, Accent)
- UVs: Properly unwrapped with no overlaps

**Export Settings (FBX):**
```
- Smooth Groups: ON
- Apply Modifiers: ON
- All Meshes: ON
- All Materials: ON
- Triangulate Faces: ON
- Axes: Forward -Y, Up Z (Unreal convention)
- Scale: 1.0
```

### 1.3 Create Hologram Effect Asset
**File:** `Hologram.blend`

**Purpose:** Animated mesh for UE5 import

**Specifications:**
- UV-mapped sphere or custom shape
- Keyframe animation: Scale (1.0 → 1.2 → 0.8) and Opacity fade
- Duration: 4 seconds
- Export as Skeletal Mesh with armature (even if 1 bone)

**Export Settings (FBX):**
```
- Deformation: ON (for skeletal mesh)
- All Bones: ON
- All Animations: ON
- NLA Strips: ON (for multiple animation clips)
```

---

## Part 2: Material Setup for Cyberpunk Aesthetic

### 2.1 Emission Settings for Glow
In Blender, use **Shader Editor:**

```glsl
// Hologram Material
Shader Layout:
  - Base Color: RGB(0, 255, 100) [Cyan-Green]
  - Emission: RGB(0, 255, 100)
  - Emission Strength: 5.0
  - Metallic: 0.8
  - Roughness: 0.2

// Primary Construct Material
  - Base Color: RGB(60, 60, 80) [Dark Blue-Gray]
  - Emission: RGB(0, 200, 50)
  - Emission Strength: 2.0
  - Metallic: 1.0
  - Roughness: 0.1
```

### 2.2 Glitch Effect (Optional - Advanced)
Use Geometry Nodes to procedurally create glitch:
- Random displacement on XY axis
- Color shift (RGB offset)
- Opacity variation
- Animate with noise texture

---

## Part 3: Animation & Keyframing

### 3.1 Main Cinematic Animation
**Key animations to set up:**

1. **Title Appearance (0-1s)**
   - Scale: (0, 0, 1) → (1, 1, 1)
   - Opacity: 0 → 1
   - Location: offset by (2, 0, 0), then to origin

2. **Neural Grid Animation (1-3s)**
   - Grid nodes animate in sequence
   - Connections draw using line render
   - Pulsing glow intensity: 0.5 → 2.0 → 0.5

3. **Construct Morph (3-5s)**
   - Shapekey animation: Base → Awakened form
   - Scale: 0.5 → 1.5 → 1.0
   - Rotation: 0° → 360° (smooth)
   - Emission strength: 1.0 → 5.0

4. **Final Transition (5-6s)**
   - Camera zoom back
   - Lighting shift to cool blue
   - Fade to white screen

### 3.2 Easing & Polish
- Use Bezier curves for smooth easing (not linear)
- Ease-in for first 10 frames, ease-out for last 10
- Overshoot on key transforms for impact

---

## Part 4: Rendering & Export

### 4.1 Render Settings
**Cycles Render Engine:**
```
- Samples: 256 (balance quality vs render time)
- Denoising: OptiX or OpenImageDenoise
- Device: GPU (CUDA/OptiX if available)
- Format: PNG or EXR for intermediate
- Bit Depth: 16-bit for color grading flexibility
```

**Output Settings:**
```
- Format: Video → H.264 MP4
- Bitrate: 50-100 Mbps (high quality)
- Container: MPEG-4
- Audio Codec: AAC
- Resolution: 1920 x 1080
- Frame Rate: 30 fps
```

### 4.2 Render to Video
1. Open **Render Properties**
2. Set Output Path: `//Cinematics/Intro_Main/Intro_Video.mp4`
3. Click **Render → Render Animation** (or `Shift+F12`)
4. Wait for render to complete (~30-60 min depending on hardware)

### 4.3 Export Static Meshes (for UE5)
**For NetPConstruct:**
```
File → Export → Autodesk FBX (.fbx)
  - Selection Only: OFF
  - Apply Modifiers: ON
  - Smooth Groups: ON
  - Scale: 1.0
  - Forward: -Y Forward
  - Up: Z Up
  - Save: /Content/Models/NetPConstruct.fbx
```

**For Hologram (Skeletal Mesh):**
```
File → Export → Autodesk FBX (.fbx)
  - Selection Only: OFF
  - Deformation: ON
  - Armature: ON
  - Animation: ON
  - Scale: 1.0
  - Save: /Content/Models/Hologram.fbx
```

---

## Part 5: Import into Unreal Engine 5

### 5.1 Import MP4 Video
1. **Content Browser** → Right-click → **New Folder** → `Cinematics/Intro_Main`
2. Drag `Intro_Video.mp4` into Content Folder
3. Import with defaults:
   - **Media Player** asset auto-created
   - **Media Texture** auto-created
   - Place into **Material** for playback on screen quad

### 5.2 Import FBX Models
1. **Content Browser** → Right-click → **Import**
2. Select `NetPConstruct.fbx`
3. Settings:
   ```
   - Skeletal Mesh: OFF (static mesh)
   - Import Normals: ON
   - Import Materials: ON
   - Create Physics Asset: OFF (for static)
   - Material Import Method: Create Materials
   ```
4. Click **Import**

**For Hologram.fbx:**
```
   - Skeletal Mesh: ON
   - Import Materials: ON
   - Import Morphs: ON
   - Create Physics Asset: OFF
   - Skeleton: Create New Skeleton
```

### 5.3 Set Up Materials in UE5
1. **Content Browser** → Create Material → `M_Hologram`
2. In **Material Editor:**
   ```
   Base Color: Linear Color (0, 1.0, 0.4) [Cyan]
   Emission Color: 1.0
   Metallic: 0.8
   Roughness: 0.2
   ```
3. Apply to imported mesh
4. Repeat for other materials as needed

### 5.4 Set Up Intro Actor
1. Place `AIntroSequence` actor in intro level
2. Assign:
   - `CinematicMediaPlayer` → Reference to Media Player asset
   - `CinematicMediaTexture` → Reference to Media Texture asset
   - `NetPConstructMesh` → NetPConstruct static mesh
   - `HologramMesh` → Hologram skeletal mesh
   - `HologramMaterial` → M_Hologram material

---

## Part 6: Audio Integration

### 6.1 Create/Import Audio
- Create or source intro music (cyberpunk theme, 6 seconds, 320 kbps)
- Mix to mono or stereo
- Normalize levels (-3dB peak)
- Export as `.wav` (16-bit, 48kHz for UE5 standard)

### 6.2 Import into UE5
1. **Content Browser** → Right-click → **Import**
2. Select `Intro_Audio.wav`
3. Settings:
   ```
   - Source File Compressed: OFF
   - Create Cue: ON (auto-creates USoundCue)
   - Volume Multiplier: 1.0
   ```
4. Click **Import**

### 6.3 Trigger Audio Playback
In `IntroSequence.cpp`, modify `PlayCinematicAudio()`:
```cpp
void AIntroSequence::PlayCinematicAudio()
{
    if (!bPlayCinematicAudio) return;
    
    // Load audio asset
    USoundBase* IntroAudio = LoadObject<USoundBase>(nullptr, 
        TEXT("SoundWave'/Game/Audio/Intro_Audio.Intro_Audio'"));
    
    if (IntroAudio)
    {
        UGameplayStatics::PlaySound2D(GetWorld(), IntroAudio, 1.0f);
    }
}
```

---

## Part 7: Testing & Troubleshooting

### Common Issues & Solutions

**Problem:** Model appears too small/large in UE5
- **Solution:** Check scale on export. UE5 default unit = 1 cm. Set FBX scale to 100 if exporting from Blender (which uses 1 unit = 1 meter by default)

**Problem:** Materials look washed out (no glow)
- **Solution:** Enable **Bloom** post-process in Level → Post Process Volume. Set Bloom Intensity to 2.0+

**Problem:** Video stutters or plays at wrong speed
- **Solution:** Check frame rate (should be 30 fps). Verify Media Player → Media Playlist source

**Problem:** Intro text is hard to read**
- **Solution:** Add **Glow** layer (Emission shader in Blender). Increase contrast with black background

### Performance Optimization
- Limit video bitrate to 50 Mbps (balance quality vs file size)
- Use LOD 0 only for intro cinematic (no need for multiple LODs)
- Disable shadow casting for intro-only meshes
- Use simple materials during intro sequence

---

## Checklist: Blender → UE5 Intro Pipeline

- [ ] **Blender Scene Created**
  - [ ] IntroSequence.blend (6-second cinematic)
  - [ ] NetPConstruct.blend (static mesh)
  - [ ] Hologram.blend (skeletal mesh with animation)

- [ ] **Materials & Lighting**
  - [ ] Emission shaders configured
  - [ ] Cyberpunk color palette (#00FF00, #00AA00, #0a0a0a)
  - [ ] Key/fill/rim lighting set up

- [ ] **Animation & Keyframes**
  - [ ] All transforms smooth with easing
  - [ ] 6-second duration total
  - [ ] Camera movement defined

- [ ] **Rendering**
  - [ ] H.264 MP4 rendered at 1920×1080 @ 30fps
  - [ ] Audio mixed and exported as .wav

- [ ] **Unreal Import**
  - [ ] MP4 imported as Media Texture
  - [ ] FBX static/skeletal meshes imported
  - [ ] Materials created and applied
  - [ ] IntroSequence actor placed in level

- [ ] **Testing**
  - [ ] Intro plays start-to-finish without errors
  - [ ] Audio syncs with video
  - [ ] Skip button works
  - [ ] Transitions to main game successfully

---

## Advanced: Procedural Glitch Effects (Optional)

For a more advanced cyberpunk feel, use Blender **Geometry Nodes:**

1. Add Geometry Nodes modifier to construct mesh
2. Create node setup:
   - **Random Value** → Controls glitch intensity
   - **Separate XYZ** → Offset per axis
   - **Color Ramp** → RGB shift
   - **Animate via drivers** (linked to timeline)

3. Keyframe the glitch intensity to peak during "awakening" phase

This creates a procedural glitch that can be controlled via parameters in UE5's material system.

---

**Next Steps:**
1. Create the Blender scenes following this guide
2. Render and export assets
3. Import into UE5 following the UE5 section
4. Compile and test in-game
5. Adjust timing/visuals as needed

Good luck with your R3ALN3T.EXE intro! 🚀

# R3ALN3T.EXE — 4K Shading & Visual Pipeline Specification
## For UE5 R3ALN3T_UE5 Project

**Version:** 1.0  
**Target:** Unreal Engine 5.4+  
**Resolution:** 3840×2160 (Native 4K)  
**Last Updated:** 2026-06-30

---

## 1. MASTER MATERIAL — MPC_SoulState

### Parameter Collection: `MPC_SoulState`
| Parameter | Type | Range | Purpose |
|-----------|------|-------|---------|
| `SoulState_Normal` | float | 0.0–1.0 | Drives all 7 aura bands, NPC dialogue tiers, NetP mirror lag |
| `Combo_ChainLength` | float | 1.0–5.0 | Drives CODE BREAK visual intensity |
| `Combo_ActiveCode` | float | 0.0–23.0 | Greek letter index for combo glyph display |
| `bInBattle` | bool | 0/1 | Toggles battle-specific VFX on/off |

### Material Layer: `M_NetP_Aura`
A sphere-component post-process material attached to NetP root bone.
```
SoulState_Normal → Lerp across 7 color stops:
  0.00–0.10: #FFE8A3 → #FFFFFF (Radiant) — soft radial pulse, slow rhythm
  0.11–0.25: #A3C4FF (Grounded) — steady glow, no pulse
  0.26–0.40: #FFB347 (Weathered) — dim flicker, faint dust particles
  0.41–0.59: Transparent (Gray) — aura opacity = 0
  0.60–0.74: #C39BD3 (Strained) — faint flicker, static burst
  0.75–0.89: #8B0000 + violet (Fractured) — erratic pulse, edge fraying, noise distortion
  0.90–1.00: #1A0000 + deep red (Corrupted) — heavy distortion, black smoke, vignette
```

### NetP Mirror Lag
Navi aura renders at 60% scale of player aura with 0.5s lag.  
Implemented via Timeline in NetP Blueprint that interpolates toward `MPC_SoulState.SoulState_Normal` over 0.5s.

---

## 2. 4×4 BATTLE GRID SHADING

### Grid Tile Material: `M_GridTile`
| Property | Value | Notes |
|----------|-------|-------|
| Metallic | 0.9 | High-reflectance holographic surface |
| Roughness | 0.15 | Mirror-like with slight diffusion |
| Emissive | Panner Node | Micro-grid scanline overlay on metallic base |
| Tile Size | 100×100×10cm | Single mesh instance, BP_GridTile |
| Player Side | Purple/Neon (#9900FF → #FF44AA) | Per-side glow via material parameter |
| Enemy Side | Teal/Grey (#00CCBB → #556666) | Per-side glow via material parameter |

### Custom Gauge Display
Fill rate: 20% per second (5s to full).  
Displayed as a glowing ring or bar on the bottom of the battle HUD.  
When full (100%), the player can execute a special **Custom Skill** — a per-NetP signature ability.

### Tile Ownership Enforcement
```cpp
// From BattleGridManager.cpp
if (TargetPos.X < 0 || TargetPos.X >= MaxCols || ...) return false;
float SideOffset = (CurrentSide == ETileSide::EnemySide) ? 900.0f : 0.0f;
OutWorldLocation = FVector(TargetPos.X * TileSpacing + SideOffset, ...);
```
- X dimensions are local to each 4×4 field (0–3 per side)
- 900-unit gap between player and enemy grids
- MCADMIN override can bypass tile restrictions

---

## 3. HOLOGRAPHIC INTERFACE (UMG)

### Terminal Text Effect (Typewriter)
```
BP: WBP_TerminalMessage
- Text appears character by character at configurable speed
- SFX: Typewriter click per character
- Glitch effect: RGB split + noise on frame 1 of each line
- Background: Semi-transparent dark panel with scanline overlay
```

### Chip Cards (Krita → PNG → UMG)
- Resolution: 256×256 pixels per chip icon
- Format: RGBA PNG, no compression
- Import to UE5 as `User Interface 2D` texture group
- Each Greek letter code gets a unique border color:
  | Rarity | Border | Alpha/Omega Special |
  |--------|--------|-------------------|
  | Common (Α–Γ) | Grey | — |
  | Uncommon (Δ–Η) | Green | — |
  | Rare (Θ–Ν) | Blue | — |
  | Epic (Ξ–Τ) | Purple | — |
  | Legendary (Υ–Ψ) | Gold | — |
  | Mythic (Ω) | Red pulsating | "GIGA" tag overlay |

---

## 4. POST-PROCESS & PARTICLES

### ScreenGlitch Post-Process Material
```
Source renders: RGB split (1-2px offset), scanlines (3px interval),
noise overlay (grain), chromatic aberration on edges
Triggered by: Terminal glitch events, DarkN3T zone entry, high corruption
```

### Rift VFX (Niagara System)
```
Used in: Act I climax (The Rift)
System: P_SectorRift
- Emissive white edge with noise distortion
- Center: screaming static texture with layered whisper audio
- Screen edges: chromatic aberration intensifies on approach
- Color: White at edge → Deep violet at center
```

### CODE BREAK VFX
```
Triggered at combo chain length 5
- Greek letter glyph appears full-screen in 4K resolution
- 2x damage burst with element-colored shockwave
- Screen freeze for 2 frames, then slow-motion impact
```

---

## 5. PRODUCTION PIPELINE

| From | To | Format | Settings |
|------|----|--------|----------|
| Blender → UE5 | Static/Skeletal Mesh | FBX | Scale: Apply All Transforms. Up: Z, Forward: -Y. Smoothing: Face |
| Blender → UE5 (Nanite) | High-poly static | FBX/glTF | Enable Nanite on import, let UE generate LODs |
| Krita → UE5 | UI elements | PNG | RGBA, 2048×2048 max, No compression |
| Material Maker → UE5 | PBR textures | PNG/TGA | Export: Albedo, Normal, ORM, Emissive. 2K world, 4K heroes |
| Quixel Bridge → UE5 | Megascans | Auto .uasset | Pick Nanite + High quality |
| Audacity → UE5 | Audio | WAV | 16-bit 44.1kHz (SFX), 24-bit 48kHz (music), Mono for 3D |
| Mixamo → UE5 | Animation | FBX | FBX for Unity format, no skin, retarget in Blender first |

### Check Before Export
- [ ] Apply All Transforms (Ctrl+A) in Blender
- [ ] UV Channel 0 = textures, Channel 1 = Lightmap (no overlaps)
- [ ] Materials named properly (not Material.001)
- [ ] Pivot at world origin (0,0,0)
- [ ] Skeletal meshes: "Add Leaf Bones" unchecked
- [ ] Collision: UCX_ prefix or UE5 auto-convex

---

## 6. PERFORMANCE TARGETS (4K @ 60fps)

| Metric | Target | Notes |
|--------|--------|-------|
| Grid tile draw calls | 2 (1 instance per side) | BP_GridTile with instanced static mesh |
| NetP character tris | <50K per character | Nanite handles >50K automatically |
| Texture pool | 4GB VRAM minimum | 4K textures require headroom |
| Post-process | Single pass | Combine glitch + bloom + tonemapping |
| Niagara particles | <500 simultaneous | Rift, CODE BREAK, and aura only |

# R3ALN3T.EXE Blender Protocol
## Integrated NetP Character Creation Pipeline

**Version:** 2.0  
**Author:** R3ALN3T.EXE Game Systems  
**Last Updated:** 2026-06-29  
**Blender Version:** 4.1+ (LTS recommended)  
**Python API:** `bpy`  

---

## 1. Protocol Overview

This document establishes the **Blender integration protocol** for generating **3D NetP (Network Persona) characters** from the `generate_netp.py` card generation pipeline. It bridges the procedural card data (CSV/JSON) with Blender's Python API (`bpy`) to produce:

- **Base mesh constructs** per alignment + element + tier
- **Procedural materials** mapped to element color palettes
- **Rigged skeletons** for poseable renders
- **Rendered card art** (PNG) injected back into the card generator
- **Export packages** (FBX/OBJ/glTF) for game engine import

---

## 2. Directory Structure

```
R3ALN3T.EXE_game_creation/
├── scripts/
│   └── Card Creation/
│       └── cards/
│           ├── characters.csv
│           ├── generated_cards.csv
│           ├── generate_netp.py          ← Python card generator
│           └── Cards/                    ← 2D card PNG output
│
├── blender/
│   ├── protocols/                        ← This document
│   ├── templates/
│   │   ├── base_humanoid.blend           ← Base mesh library
│   │   ├── base_mechanical.blend
│   │   ├── base_angelic.blend
│   │   ├── base_demonic.blend
│   │   ├── base_abyssal.blend
│   │   ├── base_viral.blend
│   │   └── base_celestial.blend
│   ├── materials/
│   │   ├── mat_fire.blend                ← Element material libraries
│   │   ├── mat_ice.blend
│   │   ├── mat_void.blend
│   │   └── ... (18 elements)
│   ├── rigs/
│   │   └── netp_rig_v2.blend             ← Standardized armature
│   ├── scripts/
│   │   ├── netp_builder.py               ← MAIN BUILD SCRIPT
│   │   ├── mat_applier.py
│   │   ├── rig_auto.py
│   │   ├── render_card.py
│   │   └── exporter.py
│   └── output/
│       ├── renders/                      ← Card art renders (PNG)
│       ├── meshes/                       ← Exported mesh files
│       └── animations/                   ← Pose clips
```

---

## 3. Data Contract (Card → Blender)

The Blender pipeline consumes **card metadata** exported from `generate_netp.py`. Each card produces a JSON sidecar:

### 3.1 Input JSON Schema

```json
{
  "card_id": "042",
  "name": "ALPHA AETHERION EMBER SENTINEL",
  "fused_identity": "Aetherion",
  "tier": "ALPHA",
  "element": "Fire",
  "alignment": "Angelic",
  "role": "Sentinel",
  "stats": {
    "hp": 1850,
    "attack": 385,
    "rapid": 278,
    "charge": 290,
    "defense": 265
  },
  "colors": {
    "primary": [255, 69, 0],
    "secondary": [255, 140, 0],
    "glow": [255, 215, 0],
    "dark": [139, 0, 0]
  },
  "construct_class": "ALPHA-RANK [FIRE] NetP",
  "signature_program": "Ember Cataclysm [S // 200]",
  "body_type": "winged_humanoid",
  "height": 1.85,
  "proportions": {
    "head": 0.12,
    "torso": 0.35,
    "arms": 0.28,
    "legs": 0.35
  }
}
```

### 3.2 Field Mapping

| JSON Field | Blender Target | Description |
|-----------|----------------|-------------|
| `alignment` | Base mesh template | Selects `.blend` template file |
| `element` | Material group | Selects element material library |
| `colors` | Material nodes | RGB values fed into emission/diffuse shaders |
| `tier` | Glow intensity / detail level | OMEGA = more geometry, more particles |
| `body_type` | Shape keys / morphs | Adjusts base mesh proportions |
| `height` | Scale transform | Overall character scale |
| `proportions` | Bone scaling | Non-uniform limb scaling |

---

## 4. Base Mesh Templates

### 4.1 Template Requirements

Each `.blend` template must contain:

1. **Single mesh object** named `NETP_BASE`
2. **Armature** named `NETP_RIG` (if rigged)
3. **Shape keys** for body variation (minimum 8 keys):
   - `SK_HeadSize`
   - `SK_TorsoWidth`
   - `SK_ArmLength`
   - `SK_LegLength`
   - `SK_ShoulderWidth`
   - `SK_WaistWidth`
   - `SK_MuscleMass`
   - `SK_AlignmentFeature` (wings, horns, etc.)
4. **Vertex groups** matching rig bone names
5. **UV map** named `UVMap` (standardized unwrap)
6. **Origin** at feet base (0, 0, 0)

### 4.2 Alignment → Template Mapping

| Alignment | Template File | Key Features |
|-----------|--------------|--------------|
| `Angelic` | `base_angelic.blend` | Wing bones, halo geometry, feather particles |
| `Demonic` | `base_demonic.blend` | Horn geometry, tail bone, claw hands |
| `Abyssal` | `base_abyssal.blend` | Tentacle bones, bioluminescent vents |
| `Celestial` | `base_celestial.blend` | Starfield particles, radiant aura shell |
| `Mechanical` | `base_mechanical.blend` | Panel seams, piston joints, LED strips |
| `Viral` | `base_viral.blend` | Glitch geometry, fragmented mesh, emission spikes |

---

## 5. Material System

### 5.1 Element Material Libraries

Each element has a `.blend` material library with **4 material slots**:

```
MAT_{ELEMENT}_PRIMARY     → Main body surface
MAT_{ELEMENT}_SECONDARY   → Armor / accent panels
MAT_{ELEMENT}_GLOW        → Emissive core / energy
MAT_{ELEMENT}_DARK        → Shadow / void areas
```

### 5.2 Material Node Structure (Standardized)

All materials use this node tree for consistency:

```
[Principled BSDF] ← Base color from card JSON
    ↓
[Emission] ← Glow color, strength driven by tier
    ↓
[Mix Shader] ← Controlled by "Energy Level" input (0.0–1.0)
    ↓
[Material Output]
```

**Tier-driven emission multipliers:**

| Tier | Emission Strength | Detail Level |
|------|------------------|--------------|
| PSI–PHI | 0.5 | Low-poly (≤2K tris) |
| UPSILON–SIGMA | 1.0 | Mid-poly (≤5K tris) |
| RHO–OMICRON | 2.0 | High-poly (≤10K tris) |
| XI–MU | 3.5 | Very high (≤20K tris) |
| LAMBDA–BETA | 5.0 | Ultra (≤50K tris) |
| ALPHA | 8.0 | Maximum detail |
| OMEGA | 12.0 + pulsating | Cinematic quality |

### 5.3 Procedural Texture Generation

For `Mechanical` and `Viral` alignments, generate procedural textures via Python:

```python
import bpy

def generate_panel_lines(obj, density=10):
    """Add edge-wear panel lines to mechanical constructs."""
    # Create geometry nodes modifier
    mod = obj.modifiers.new(name="PanelLines", type='NODES')
    # ... node group setup
    return mod

def generate_glitch_texture(obj, intensity=0.3):
    """Add vertex displacement for viral glitch effect."""
    mod = obj.modifiers.new(name="GlitchDisplace", type='DISPLACE')
    # ... noise texture setup
    return mod
```

---

## 6. Rigging Protocol

### 6.1 Standard Bone Hierarchy

```
NETP_RIG (root)
├── ROOT
│   ├── HIPS
│   │   ├── SPINE
│   │   │   ├── CHEST
│   │   │   │   ├── NECK
│   │   │   │   │   └── HEAD
│   │   │   │   ├── SHOULDER_L → ARM_L → FOREARM_L → HAND_L
│   │   │   │   └── SHOULDER_R → ARM_R → FOREARM_R → HAND_R
│   │   └── LEG_L → SHIN_L → FOOT_L
│   └── LEG_R → SHIN_R → FOOT_R
├── ALIGNMENT_FEATURE (wing bone, horn bone, tail bone, etc.)
└── WEAPON_BONE (optional, for weapon props)
```

### 6.2 Auto-Rigging Script Interface

```python
def auto_rig_construct(mesh_obj, alignment, proportions):
    """
    Apply standardized rig to any base mesh.

    Args:
        mesh_obj: The mesh to rig
        alignment: str — determines extra bones (wings, tail, etc.)
        proportions: dict — scales bone lengths

    Returns:
        armature_obj: The completed rig
    """
    # 1. Import standard rig from template
    # 2. Parent mesh to armature with automatic weights
    # 3. Scale bones per proportions dict
    # 4. Add alignment-specific bones
    # 5. Apply pose library (idle, combat, cast)
    pass
```

### 6.3 Pose Library

Each construct gets **3 default poses**:

| Pose Name | Use Case | Description |
|-----------|----------|-------------|
| `POSE_IDLE` | Card art / menu | Neutral stance, slight breathing |
| `POSE_COMBAT` | Battle intro | Aggressive, weapon ready |
| `POSE_CAST` | Ability animation | Channeling energy, one arm raised |

---

## 7. Rendering Protocol

### 7.1 Card Art Render Settings

**Target:** 640×480 art area inside 750×1050 card  
**Camera:** Orthographic, front-facing, slight 3/4 angle for depth  
**Lighting:** 3-point studio + element-colored rim light  
**Background:** Transparent (alpha) for card compositing  
**Output:** PNG with alpha, 150 DPI

### 7.2 Render Script

```python
import bpy

def render_card_art(construct_name, output_path, pose="POSE_IDLE"):
    """
    Render a construct for TCG card art.

    Workflow:
        1. Load construct .blend
        2. Apply pose
        3. Set camera to framed bounding box
        4. Configure Cycles render (128 samples, denoising)
        5. Render PNG with alpha
        6. Save to output_path
    """
    scene = bpy.context.scene
    scene.render.engine = 'CYCLES'
    scene.cycles.samples = 128
    scene.cycles.use_denoising = True
    scene.render.resolution_x = 640
    scene.render.resolution_y = 480
    scene.render.film_transparent = True
    scene.render.image_settings.file_format = 'PNG'
    scene.render.image_settings.color_mode = 'RGBA'
    scene.render.filepath = output_path

    # Apply pose
    armature = bpy.data.objects.get("NETP_RIG")
    if armature:
        bpy.context.view_layer.objects.active = armature
        bpy.ops.object.mode_set(mode='POSE')
        # Apply pose from library
        bpy.ops.poselib.apply_pose(pose_index=0)  # POSE_IDLE
        bpy.ops.object.mode_set(mode='OBJECT')

    # Frame camera to mesh
    camera = bpy.data.objects.get("Camera")
    mesh = bpy.data.objects.get("NETP_BASE")
    if camera and mesh:
        bpy.ops.view3d.camera_to_view_selected()

    # Render
    bpy.ops.render.render(write_still=True)
    return output_path
```

### 7.3 Batch Render from CSV

```python
def batch_render_from_csv(csv_path, output_dir):
    """
    Read generated_cards.csv and render all constructs.

    For each row:
        1. Parse alignment, element, tier
        2. Build construct via netp_builder.py
        3. Render card art PNG
        4. Update CSV 'Construct Sprites' field with actual path
    """
    import csv
    with open(csv_path, 'r') as f:
        reader = csv.DictReader(f)
        for row in reader:
            name = row['Name'].replace(' ', '_')
            alignment = row['Construct Class'].split('-')[0]  # infer
            element = row['Construct Class'].split('[')[1].replace('] NetP', '')
            tier = row['Card Number'].split('-')[0] if 'OMEGA' in row['Card Number'] else row['Name'].split(' ')[0]

            # Build
            build_construct(name, alignment, element, tier)

            # Render
            out_path = f"{output_dir}/{name}_render.png"
            render_card_art(name, out_path)

            # Update CSV reference
            row['Construct Sprites'] = out_path
```

---

## 8. Export Protocol

### 8.1 Game Engine Export Formats

| Format | Use Case | Settings |
|--------|----------|----------|
| **glTF 2.0** (.glb) | Web / Unity / Godot | Embedded textures, +Y up |
| **FBX** (.fbx) | Unreal Engine / Unity | Y-up, Z-forward, embedded media |
| **OBJ** (.obj) | Legacy / prototyping | Materials as .mtl, triangulated |
| **ABC** (.abc) | Alembic cache | Animation baked, per-frame mesh |

### 8.2 Export Script

```python
import bpy

def export_construct(construct_name, export_dir, formats=['glb', 'fbx']):
    """Export construct in multiple formats."""

    # Select only construct objects
    bpy.ops.object.select_all(action='DESELECT')
    for obj in bpy.data.objects:
        if obj.name.startswith("NETP"):
            obj.select_set(True)

    base_path = f"{export_dir}/{construct_name}"

    if 'glb' in formats:
        bpy.ops.export_scene.gltf(
            filepath=f"{base_path}.glb",
            export_format='GLB',
            export_yup=True,
            export_materials='EXPORT',
            export_animations=True
        )

    if 'fbx' in formats:
        bpy.ops.export_scene.fbx(
            filepath=f"{base_path}.fbx",
            use_selection=True,
            global_scale=1.0,
            apply_unit_scale=True,
            apply_scale_options='FBX_SCALE_UNITS',
            axis_forward='-Z',
            axis_up='Y',
            bake_anim=True,
            embed_textures=True
        )

    if 'obj' in formats:
        bpy.ops.export_scene.obj(
            filepath=f"{base_path}.obj",
            use_selection=True,
            use_materials=True,
            triangulate_faces=True
        )

    return f"Exported {construct_name} to {export_dir}"
```

---

## 9. Integration Workflow

### 9.1 Full Pipeline (Card → 3D → Card Art)

```
┌─────────────────┐     ┌─────────────────┐     ┌─────────────────┐
│  generate_netp  │────→│  netp_builder   │────→│  render_card  │
│     .py         │     │    .py          │     │    .py        │
│                 │     │                 │     │                 │
│  Generates CSV  │     │  Builds in      │     │  Renders PNG  │
│  + JSON sidecar │     │  Blender via    │     │  card art     │
│                 │     │  bpy API        │     │                 │
└─────────────────┘     └─────────────────┘     └─────────────────┘
         │                       │                       │
         ▼                       ▼                       ▼
   generated_cards.csv      construct.blend         Cards/*.png
   + metadata/*.json        + mesh exports          (final card art)
```

### 9.2 Execution Order

**Step 1:** Generate cards (Python standalone)
```bash
python scripts/Card\ Creation/cards/generate_netp.py --count 100
```

**Step 2:** Build constructs in Blender (headless or GUI)
```bash
# Headless batch build
blender --background --python blender/scripts/netp_builder.py -- --input generated_cards.csv --output blender/output/

# Or GUI mode for inspection
blender blender/templates/base_humanoid.blend --python blender/scripts/netp_builder.py
```

**Step 3:** Render card art
```bash
blender --background --python blender/scripts/render_card.py -- --input blender/output/ --cards-dir scripts/Card\ Creation/cards/Cards/
```

**Step 4:** Regenerate cards with real art paths
```bash
python scripts/Card\ Creation/cards/generate_netp.py --update-sprites --cards-dir scripts/Card\ Creation/cards/Cards/
```

---

## 10. Quality Standards

### 10.1 Polygon Budgets

| Tier | Max Tris | Texture Resolution | Material Complexity |
|------|----------|-------------------|---------------------|
| PSI–PHI | 2,000 | 512×512 | 1 material |
| UPSILON–OMICRON | 5,000 | 1K×1K | 2 materials |
| XI–MU | 10,000 | 2K×2K | 3 materials |
| LAMBDA–BETA | 25,000 | 2K×2K | 4 materials + particles |
| ALPHA | 50,000 | 4K×4K | 5 materials + complex particles |
| OMEGA | 100,000 | 4K×4K | Full shader network + volumetrics |

### 10.2 Performance Targets

- **Batch build 100 constructs:** < 30 minutes (headless, 8-core)
- **Single card art render:** < 2 minutes (Cycles, GPU)
- **Export all formats:** < 1 minute per construct
- **Memory per construct:** < 512MB VRAM (peak)

### 10.3 Validation Checklist

Before a construct is approved:

- [ ] Mesh is watertight (no holes, non-manifold edges fixed)
- [ ] UVs are 0–1 bounded, no overlapping islands
- [ ] All vertex groups match rig bone names
- [ ] Materials use standardized node trees
- [ ] Emission values match tier specification
- [ ] Pose library has 3 valid poses
- [ ] Render output is 640×480 PNG with alpha
- [ ] Export files load correctly in target engine
- [ ] File naming matches `Name` field from card data

---

## 11. Troubleshooting

| Issue | Cause | Solution |
|-------|-------|----------|
| `bpy` module not found | Running outside Blender | Use Blender's bundled Python: `blender --python` |
| Texture not applied | Material name mismatch | Ensure `MAT_{ELEMENT}_PRIMARY` exists in library |
| Rig fails to parent | Vertex group mismatch | Run `clean_vertex_groups()` before parenting |
| Render is black | Camera not aligned | Run `camera_to_view_selected()` or set camera target |
| Export too large | Embedded textures | Use external textures, compress to KTX2/WebP |
| Glitch effect crashes | Subdivision too high | Cap subdivision at 3 levels for Viral alignment |
| OMEGA glow blows out | Emission > 20 | Clamp emission at 12, use bloom in compositor |

---

## 12. API Reference

### 12.1 `netp_builder.py` — Main Build Script

```python
class NetPBuilder:
    """Orchestrates construct creation in Blender."""

    def load_template(self, alignment: str) -> bpy.types.Object:
        """Load base mesh template for alignment."""

    def apply_element_materials(self, mesh: bpy.types.Object, element: str, colors: dict):
        """Apply and tint element materials."""

    def scale_proportions(self, mesh: bpy.types.Object, proportions: dict):
        """Apply shape keys for body proportions."""

    def add_tier_effects(self, mesh: bpy.types.Object, tier: str):
        """Add glow, particles, detail based on tier."""

    def build(self, card_data: dict) -> bpy.types.Object:
        """Full build pipeline. Returns completed construct."""
```

### 12.2 `render_card.py` — Render Controller

```python
class CardArtRenderer:
    """Renders constructs for TCG card art."""

    def setup_studio(self, element: str):
        """Configure 3-point lighting + rim light."""

    def frame_subject(self, mesh: bpy.types.Object):
        """Position camera to fill frame."""

    def render(self, output_path: str, samples: int = 128) -> str:
        """Execute render and return file path."""
```

### 12.3 `exporter.py` — Export Manager

```python
class NetPExporter:
    """Handles multi-format export."""

    def export_glb(self, objects: list, path: str) -> str:
    def export_fbx(self, objects: list, path: str) -> str:
    def export_obj(self, objects: list, path: str) -> str:
    def package_all(self, construct_name: str, dir: str) -> dict:
        """Export all formats, return path dict."""
```

---

## 13. Changelog

| Version | Date | Changes |
|---------|------|---------|
| 1.0 | 2026-06-25 | Initial protocol draft |
| 2.0 | 2026-06-29 | Added full bpy API, render pipeline, export formats, quality standards |

---

## 14. License & Attribution

**R3ALN3T.EXE Game Systems**  
All constructs, materials, and rigs are proprietary game assets.  
External Blender add-ons used must be GPL-compatible where applicable.

---

*End of Protocol Document*

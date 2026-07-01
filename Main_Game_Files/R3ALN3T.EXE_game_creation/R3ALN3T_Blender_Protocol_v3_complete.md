# R3ALN3T.EXE Blender Protocol v3.0
## Integrated 3D Character Creation Pipeline

**Document Version:** 3.0  
**Game Version:** R3ALN3T.EXE  
**Hierarchy:** 16-Rank Mythos Origin Compliant  
**Alignments:** 4 Types (Mechanical, Viral, Angelic, Demonic)  
**Elements:** 18 Combat Synchronization Loops  

---

## Table of Contents

1. [Protocol Overview](#1-protocol-overview)
2. [Directory Structure](#2-directory-structure)
3. [Data Contract (JSON Schema)](#3-data-contract-json-schema)
4. [Base Mesh Templates](#4-base-mesh-templates)
5. [Material System](#5-material-system)
6. [Rigging Protocol](#6-rigging-protocol)
7. [Rendering Protocol](#7-rendering-protocol)
8. [Export Protocol](#8-export-protocol)
9. [Integration Workflow](#9-integration-workflow)
10. [Quality Standards](#10-quality-standards)
11. [Troubleshooting](#11-troubleshooting)
12. [API Reference](#12-api-reference)

---

## 1. Protocol Overview

This protocol defines the bridge between the `generate_netp.py` card generator and Blender's `bpy` API for producing production-ready 3D NetP (Network Persona) constructs.

### Pipeline Flow

```
generate_netp.py ──► generated_cards.csv ──► netp_builder.py ──► .blend files
                                                    │
                                                    ▼
                                          render_card.py ──► card PNGs
                                                    │
                                                    ▼
                                          netp_exporter.py ──► glTF/FBX/OBJ
```

### Key Principles

- **Data-Driven:** Every construct is built from CSV/JSON metadata — no manual modeling per card.
- **Modular Templates:** 4 alignment base meshes × 18 element materials = 72 variant combinations.
- **Tier Scaling:** Polygon budget, emission intensity, and detail level scale with rank (OMICRON=2K tris → OMEGA=100K tris).
- **Headless Batch:** Full pipeline runs via `blender --background --python` for automation.

---

## 2. Directory Structure

```
R3ALN3T.EXE_game_creation/
├── scripts/
│   ├── Card Creation/
│   │   ├── cards/
│   │   │   ├── characters.csv              # Source character data
│   │   │   ├── generated_cards.csv         # Card generator output
│   │   │   ├── generate_netp.py          # Card generator (this script)
│   │   │   └── Cards/                      # Generated card PNGs
│   │   └── blender/
│   │       ├── templates/
│   │       │   ├── base_mechanical.blend   # Angular armored chassis
│   │       │   ├── base_viral.blend        # Amorphous glitch form
│   │       │   ├── base_angelic.blend      # Winged humanoid
│   │       │   └── base_demonic.blend      # Horned beast
│   │       ├── materials/
│   │       │   ├── mat_fire.blend
│   │       │   ├── mat_water.blend
│   │       │   ├── ... (18 element libraries)
│   │       │   └── mat_plasma.blend
│   │       ├── rigs/
│   │       │   ├── netp_rig_base.blend     # Standard bone hierarchy
│   │       │   └── poses/
│   │       │       ├── idle.blend
│   │       │       ├── combat.blend
│   │       │       └── cast.blend
│   │       ├── scripts/
│   │       │   ├── netp_builder.py         # Main build script
│   │       │   ├── render_card.py          # Card art renderer
│   │       │   ├── netp_exporter.py        # Format exporter
│   │       │   └── utils.py                # Shared utilities
│   │       └── output/
│   │           ├── constructs/             # Final .blend per construct
│   │           ├── renders/                # Card art PNGs
│   │           └── exports/                # glTF/FBX/OBJ
│   └── ...
```

---

## 3. Data Contract (JSON Schema)

The card generator exports a JSON sidecar per card. Blender consumes this to build the 3D asset.

### Card JSON Schema

```json
{
  "card_number": "OMEGA-004",
  "tier": "OMEGA",
  "rank": 1,
  "name": "KAELTHAS TRINITY",
  "alignment": "Angelic",
  "element": "Fire",
  "faction": "CELESTIAL ORDER",
  "stats": {
    "hp": 9500,
    "atk": 820,
    "rapid": 98,
    "charge": 105,
    "defense": 720
  },
  "colors": {
    "primary": [255, 69, 0],
    "secondary": [255, 140, 0],
    "accent": [178, 34, 34],
    "glow": [255, 215, 0]
  },
  "proportions": {
    "height": 1.8,
    "wing_span": 2.4,
    "horn_length": 0.0,
    "armor_density": 0.3,
    "glitch_intensity": 0.0
  },
  "shape_keys": {
    "wing_size": 1.0,
    "horn_curve": 0.0,
    "armor_plates": 0.2,
    "tendril_count": 0,
    "aura_radius": 1.5
  },
  "moves": [
    "DIVINE.IGNITE.STRIKE",
    "DIVINE.BLAZE.SLAM",
    "DIVINE.EMBER.BARRAGE"
  ],
  "construct_sprite": "OMEGA-004_KAELTHAS_TRINITY_idle.png",
  "source_identities": ["ID.7742", "ID.3301", "ID.8894"]
}
```

### Field Mappings

| JSON Field | Blender Target | Description |
|-----------|----------------|-------------|
| `alignment` | Base mesh selection | Picks `base_{alignment}.blend` |
| `element` | Material library | Loads `mat_{element}.blend` |
| `tier` | Quality tier | Polygon budget, emission multiplier |
| `colors.*` | Material nodes | Feeds into Principled BSDF emission |
| `proportions.*` | Shape keys | Drives morph targets |
| `shape_keys.*` | Modifier values | Sculpt detail, particle count |

---

## 4. Base Mesh Templates

### 4.1 Required Shape Keys (All Templates)

Every base mesh must expose these shape keys for procedural variation:

| Shape Key | Range | Used By |
|-----------|-------|---------|
| `SK_height` | 0.5–2.0 | All |
| `SK_width` | 0.5–1.5 | All |
| `SK_wing_size` | 0.0–3.0 | Angelic |
| `SK_wing_fold` | 0.0–1.0 | Angelic |
| `SK_horn_length` | 0.0–2.0 | Demonic |
| `SK_horn_curve` | -1.0–1.0 | Demonic |
| `SK_tail_length` | 0.0–2.0 | Demonic |
| `SK_armor_plates` | 0.0–1.0 | Mechanical |
| `SK_joint_bulk` | 0.0–1.0 | Mechanical |
| `SK_sensor_count` | 0–6 | Mechanical |
| `SK_tendril_count` | 0–12 | Viral |
| `SK_glitch_intensity` | 0.0–1.0 | Viral |
| `SK_aura_radius` | 0.5–3.0 | All |

### 4.2 Required Vertex Groups

| Group | Purpose |
|-------|---------|
| `VG_head` | Head tracking, halo attachment |
| `VG_torso` | Core body deformation |
| `VG_l_arm`, `VG_r_arm` | Limb articulation |
| `VG_l_leg`, `VG_r_leg` | Limb articulation |
| `VG_wing_l`, `VG_wing_r` | Wing bones (Angelic) |
| `VG_horn_l`, `VG_horn_r` | Horn bones (Demonic) |
| `VG_tail` | Tail chain (Demonic) |
| `VG_armor_*` | Plate separation (Mechanical) |
| `VG_tendril_*` | Tendril bones (Viral) |

### 4.3 Alignment-Specific Geometry

**Angelic (`base_angelic.blend`)**
- Feathered wing meshes (subdivided planes with hair particles)
- Halo ring geometry (torus, emission shader)
- Flowing robe/cloth simulation
- Target: 15K–60K tris depending on tier

**Demonic (`base_demonic.blend`)**
- Curved horn meshes (beveled curves)
- Barbed tail (curve with taper + spike instances)
- Scaled hide (displacement on body)
- Burning eye sockets (emissive spheres)
- Target: 18K–70K tris depending on tier

**Mechanical (`base_mechanical.blend`)**
- Plate segments (separate mesh objects, rigid body ready)
- Hydraulic joint cylinders
- Optical sensor lenses (glass BSDF)
- Exposed wiring (curve objects with bevel)
- Target: 12K–50K tris depending on tier

**Viral (`base_viral.blend`)**
- Amorphous blob body (metaball or heavily subdivided sphere)
- Tendril curves (procedural, animated)
- Glitch particle system (geometry nodes)
- Bio-luminescent patches (emission vertex paint)
- Target: 20K–80K tris depending on tier

---

## 5. Material System

### 5.1 Element Material Libraries

Each `mat_{element}.blend` contains a node group `NG_Element_{Element}` with these inputs:

| Input | Type | Range | Description |
|-------|------|-------|-------------|
| `PrimaryColor` | RGB | 0–1 | Base diffuse |
| `SecondaryColor` | RGB | 0–1 | Secondary detail |
| `AccentColor` | RGB | 0–1 | Emission/highlight |
| `EmissionStrength` | Float | 0–20 | Glow intensity |
| `Roughness` | Float | 0–1 | Surface roughness |
| `Metallic` | Float | 0–1 | Metalness |
| `Subsurface` | Float | 0–1 | SSS weight |
| `DetailScale` | Float | 0–10 | Procedural texture scale |

### 5.2 Tier-Driven Emission Multiplier

| Tier | Emission Multiplier | Glow Bloom | Particle Count |
|------|---------------------|------------|----------------|
| OMEGA | 12.0 | Extreme | 5000 |
| ALPHA | 8.0 | High | 3000 |
| BETA | 5.0 | Medium-High | 2000 |
| GAMMA | 3.5 | Medium | 1500 |
| DELTA | 2.5 | Low-Medium | 1000 |
| EPSILON | 1.8 | Low | 700 |
| ZETA | 1.4 | Subtle | 500 |
| ETA–OMICRON | 1.0 | Minimal | 200–50 |

### 5.3 Procedural Texture Presets

Each element has a unique procedural signature:

| Element | Procedural Signature |
|---------|---------------------|
| Fire | Voronoi F2-F1 → ColorRamp (orange→red→black) → Emission |
| Water | Wave texture → Bump → Glass BSDF + Caustics proxy |
| Lightning | Noise → Threshold → Emission (strobe animation) |
| Ice | Musgrave → Displacement + Subsurface Scattering |
| Wind | Noise → Vertex Displacement + Transparency falloff |
| Earth | Voronoi → Displacement + ColorRamp (brown→green) |
| Light | Gradient → Emission + Volume Scatter |
| Dark | Blackbody → Emission (very low) + Absorption |
| Void | Nothing. Pure black with edge emission. |
| Metal | Brushed metal (Anisotropic) + scratch maps |
| Nature | Leaf particle system + moss displacement |
| Sound | Ripple wave (animated) + iridescent sheen |
| Gravity | Distorted grid + darkening gradient |
| Time | Animated noise (temporal offset per frame) |
| Blood | Subsurface + wet specular + vein displacement |
| Poison | Green subsurface + bubble displacement |
| Crystal | Refraction + dispersion + fracture geometry |
| Plasma | Emission + volume scatter + animated turbulence |

---

## 6. Rigging Protocol

### 6.1 Standard Bone Hierarchy

```
ROOT
├── COG (Center of Gravity)
│   ├── spine.001
│   │   ├── spine.002
│   │   │   ├── spine.003
│   │   │   │   ├── neck
│   │   │   │   │   └── head
│   │   │   │   ├── shoulder.L
│   │   │   │   │   └── arm.L
│   │   │   │   │       └── forearm.L
│   │   │   │   │           └── hand.L
│   │   │   │   └── shoulder.R
│   │   │   │       └── arm.R
│   │   │   │           └── forearm.R
│   │   │   │               └── hand.R
│   │   │   └── hip.L
│   │   │   │   └── thigh.L
│   │   │   │       └── shin.L
│   │   │   │           └── foot.L
│   │   │   └── hip.R
│   │   │       └── thigh.R
│   │   │           └── shin.R
│   │   │               └── foot.R
│   │   └── [ALIGNMENT SPECIFIC]
│   │       ├── wing.L (Angelic)
│   │       ├── wing.R (Angelic)
│   │       ├── horn.L (Demonic)
│   │       ├── horn.R (Demonic)
│   │       ├── tail.001→tail.005 (Demonic)
│   │       ├── armor.001→armor.012 (Mechanical)
│   │       └── tendril.001→tendril.012 (Viral)
```

### 6.2 Auto-Rigging Interface

```python
# netp_builder.py - Rigging snippet
def auto_rig_construct(construct_data: dict, armature: bpy.types.Armature):
    alignment = construct_data["alignment"]

    # Load base rig
    base_rig_path = f"templates/base_{alignment.lower()}.blend"
    append_object(base_rig_path, "Armature", "netp_rig")

    # Apply shape keys from data
    for key, value in construct_data["shape_keys"].items():
        obj = bpy.context.active_object
        if key in obj.data.shape_keys.key_blocks:
            obj.data.shape_keys.key_blocks[key].value = value

    # Parent alignment-specific meshes to bones
    if alignment == "Angelic":
        parent_wings_to_bones(obj, armature)
    elif alignment == "Demonic":
        parent_horns_to_bones(obj, armature)
        setup_tail_ik(armature, chain_length=5)
    elif alignment == "Mechanical":
        setup_plate_constraints(obj, armature)
    elif alignment == "Viral":
        setup_tendril_physics(obj, armature)
```

### 6.3 Pose Library

Three standard poses per construct:

| Pose | File | Description |
|------|------|-------------|
| Idle | `poses/idle.blend` | Standing, breathing, subtle movement |
| Combat | `poses/combat.blend` | Aggressive stance, weapon ready |
| Cast | `poses/cast.blend` | Channeling element, arms raised |

Pose application:
```python
bpy.ops.pose.lib.apply_pose(pose_index=0)  # idle
```

---

## 7. Rendering Protocol

### 7.1 Card Art Render Settings

```python
# render_card.py settings
RENDER_SETTINGS = {
    "resolution": (640, 480),      # Card art aspect ratio
    "engine": "CYCLES",
    "samples": 256,                # OMEGA=512, OMICRON=128
    "denoising": True,
    "transparent_background": True,  # For card compositing
    "output_format": "PNG",
    "color_depth": "16",
    "view_transform": "AgX",       # or "Filmic" for older Blender
    "look": "High Contrast",
}
```

### 7.2 Camera Setup

```python
def setup_card_camera():
    cam = bpy.data.cameras.new("CardArtCamera")
    cam_obj = bpy.data.objects.new("CardArtCamera", cam)
    bpy.context.collection.objects.link(cam_obj)

    # 3/4 view, slightly elevated
    cam_obj.location = (2.5, -3.5, 2.0)
    cam_obj.rotation_euler = (1.1, 0, 0.6)

    cam.type = 'PERSP'
    cam.lens = 50  # mm
    cam.sensor_width = 36

    # Depth of field for OMEGA/ALPHA
    cam.dof.use_dof = True
    cam.dof.focus_distance = 4.0
    cam.dof.aperture_fstop = 2.8
```

### 7.3 Lighting Rig

```python
def setup_card_lights(element: str, tier: str):
    """Three-point lighting + element-specific accent."""

    # Key light (warm)
    key = create_light("Key", "AREA", (3, -4, 4), 1000, (1.0, 0.95, 0.9))

    # Fill light (cool)
    fill = create_light("Fill", "AREA", (-3, -2, 3), 400, (0.8, 0.9, 1.0))

    # Rim light (element color)
    elem_color = ELEMENT_COLORS[element]
    rim = create_light("Rim", "SPOT", (0, 3, 2), 800, elem_color)

    # Tier accent: OMEGA gets volumetric god rays
    if tier == "OMEGA":
        vol = create_volume_scatter("GodRays", density=0.1)
```

### 7.4 Batch Render from CSV

```bash
# Render all OMEGA cards
blender --background \
    --python blender/scripts/render_card.py \
    -- --input generated_cards.csv \
       --filter "tier=OMEGA" \
       --output Cards/

# Render specific card
blender --background \
    --python blender/scripts/render_card.py \
    -- --card "OMEGA-004"
```

---

## 8. Export Protocol

### 8.1 Supported Formats

| Format | Extension | Use Case | Notes |
|--------|-----------|----------|-------|
| glTF 2.0 | `.gltf` / `.glb` | Web, Godot, Three.js | **Preferred** — PBR materials, animations |
| FBX | `.fbx` | Unity, Unreal, Maya | Industry standard, widely supported |
| OBJ | `.obj` | Legacy, simple import | No animation, basic materials |
| Alembic | `.abc` | VFX, simulation cache | Point cache for Viral tendrils |
| USD | `.usd` | Pixar pipeline, Omniverse | Emerging standard |

### 8.2 Export Settings per Format

**glTF 2.0 (Recommended)**
```python
def export_gltf(filepath: str, obj: bpy.types.Object):
    bpy.ops.export_scene.gltf(
        filepath=filepath,
        export_format='GLB',
        export_textures=True,
        export_materials='EXPORT',
        export_animations=True,
        export_skins=True,
        export_morph=True,
        export_draco_mesh_compression_enable=True,  # For web
        export_draco_mesh_compression_level=6,
    )
```

**FBX (Unity/Unreal)**
```python
def export_fbx(filepath: str, obj: bpy.types.Object):
    bpy.ops.export_scene.fbx(
        filepath=filepath,
        use_selection=True,
        global_scale=1.0,
        apply_unit_scale=True,
        apply_scale_options='FBX_SCALE_NONE',
        axis_forward='-Z',
        axis_up='Y',
        bake_space_transform=True,
        use_mesh_edges=False,
        use_tspace=True,
        use_custom_props=True,
        add_leaf_bones=False,
        primary_bone_axis='Y',
        secondary_bone_axis='X',
        use_armature_deform_only=False,
        bake_anim=True,
        bake_anim_use_all_bones=True,
        bake_anim_use_nla_strips=False,
        bake_anim_use_all_actions=True,
        bake_anim_force_startend_keying=True,
    )
```

### 8.3 Export Directory Structure

```
output/exports/
├── gltf/
│   ├── OMEGA-004_KAELTHAS_TRINITY.glb
│   ├── ALPHA-101_XENORION_SERAPH.glb
│   └── ...
├── fbx/
│   ├── OMEGA-004_KAELTHAS_TRINITY.fbx
│   └── ...
├── obj/
│   └── ...
└── alembic/
    └── ... (Viral constructs only)
```

---

## 9. Integration Workflow

### 9.1 Full Pipeline (One Command)

```bash
# Step 1: Generate cards
python scripts/Card\ Creation/cards/generate_netp.py --count 100

# Step 2: Export JSON sidecars
python scripts/Card\ Creation/cards/generate_netp.py --count 100 --export-json

# Step 3: Build 3D constructs in Blender
blender --background \
    --python scripts/Card\ Creation/blender/scripts/netp_builder.py \
    -- --input scripts/Card\ Creation/cards/generated_cards.csv \
       --json-dir scripts/Card\ Creation/cards/json/

# Step 4: Render card art
blender --background \
    --python scripts/Card\ Creation/blender/scripts/render_card.py \
    -- --input scripts/Card\ Creation/cards/generated_cards.csv \
       --output scripts/Card\ Creation/cards/Cards/

# Step 5: Export game-ready assets
blender --background \
    --python scripts/Card\ Creation/blender/scripts/netp_exporter.py \
    -- --format gltf \
       --output scripts/Card\ Creation/blender/output/exports/
```

### 9.2 Single Card Workflow

```bash
# Build + render + export one card
blender --background \
    --python scripts/Card\ Creation/blender/scripts/full_pipeline.py \
    -- --card "OMEGA-004" \
       --build \
       --render \
       --export gltf,fbx
```

### 9.3 Continuous Integration

Recommended for large batches (1000+ cards):

```python
# ci_batch.py
import subprocess
import csv

BATCH_SIZE = 50
MAX_PARALLEL = 4

def process_batch(cards: list):
    # Write batch CSV
    # Launch Blender instances
    # Collect outputs
    # Merge into final dataset
    pass
```

---

## 10. Quality Standards

### 10.1 Polygon Budget per Tier

| Tier | Tris Target | Tris Hard Limit | Texture Resolution |
|------|-------------|-------------------|-------------------|
| OMEGA | 80K–100K | 120K | 4K |
| ALPHA | 50K–70K | 90K | 4K |
| BETA | 30K–50K | 65K | 2K |
| GAMMA | 20K–35K | 45K | 2K |
| DELTA | 12K–22K | 30K | 1K |
| EPSILON | 8K–15K | 20K | 1K |
| ZETA | 5K–10K | 14K | 1K |
| ETA | 4K–8K | 10K | 512 |
| THETA | 3K–6K | 8K | 512 |
| IOTA | 2.5K–5K | 7K | 512 |
| KAPPA | 2K–4K | 6K | 512 |
| LAMBDA | 1.8K–3.5K | 5K | 256 |
| MU | 1.5K–3K | 4.5K | 256 |
| NU | 1.2K–2.5K | 4K | 256 |
| XI | 1K–2K | 3.5K | 256 |
| OMICRON | 0.8K–1.5K | 3K | 256 |

### 10.2 Performance Targets

| Metric | Target | Notes |
|--------|--------|-------|
| Build time per card | <30s | Headless, mid-tier hardware |
| Render time per card | <60s | Cycles, 256 samples |
| Export time per card | <10s | glTF with Draco |
| Memory per Blender instance | <4GB | For parallel batching |
| File size (glTF) | <10MB | OMEGA with textures |

### 10.3 Visual Standards

- **Silhouette readability:** Construct must be identifiable at 64×64px thumbnail.
- **Element readability:** Primary element must be obvious at a glance.
- **Tier differentiation:** OMEGA must feel "more" than OMICRON — glow, detail, presence.
- **Alignment differentiation:** Mechanical vs Viral must look fundamentally different.

---

## 11. Troubleshooting

### 11.1 Common bpy Issues

| Issue | Cause | Fix |
|-------|-------|-----|
| `ModuleNotFoundError: bpy` | Running outside Blender | Use `blender --python`, not `python` |
| `Context is incorrect` | bpy requires 3D view context | Use `override` or `context.temp_override()` |
| `Object not found` | Appended objects not linked | Check `bpy.data.objects` vs `bpy.context.collection` |
| `Shape key not found` | Missing basis key | Ensure basis shape key exists before adding others |
| `Material pink` | Missing texture files | Pack textures into .blend or use absolute paths |
| `Render is black` | No lights / camera | Verify scene has both; check world background |
| `Export missing animations` | Actions not pushed to NLA | Use `bake_anim_use_nla_strips=True` or push down |

### 11.2 Performance Issues

| Symptom | Cause | Fix |
|---------|-------|-----|
| Build takes >5min | Too many subdivisions | Reduce subdivision levels for low tiers |
| Render crashes | Out of VRAM | Reduce samples, use CPU render, or tile size |
| Memory leak | Not freeing bpy data | Call `bpy.data.meshes.remove(mesh)` after export |
| Parallel slowdown | GIL contention | Use multiprocessing, not threading |

---

## 12. API Reference

### 12.1 NetPBuilder Class

```python
class NetPBuilder:
    """Builds a NetP construct from card data."""

    def __init__(self, template_dir: str, material_dir: str):
        self.template_dir = Path(template_dir)
        self.material_dir = Path(material_dir)

    def build(self, card_data: dict) -> bpy.types.Object:
        """
        Build a complete construct.

        Args:
            card_data: Dictionary matching the JSON schema.

        Returns:
            The root object of the constructed mesh.
        """
        pass

    def load_base_mesh(self, alignment: str) -> bpy.types.Object:
        """Load and return the base mesh for an alignment."""
        pass

    def apply_material(self, obj: bpy.types.Object, element: str, 
                       colors: dict, tier: str) -> None:
        """Apply element material with tier-driven emission."""
        pass

    def apply_shape_keys(self, obj: bpy.types.Object, 
                         shape_keys: dict) -> None:
        """Apply all shape key values from card data."""
        pass

    def auto_rig(self, obj: bpy.types.Object, 
                 alignment: str) -> bpy.types.Armature:
        """Auto-rig the construct based on alignment."""
        pass
```

### 12.2 CardArtRenderer Class

```python
class CardArtRenderer:
    """Renders card art PNGs from constructed meshes."""

    def __init__(self, output_dir: str):
        self.output_dir = Path(output_dir)

    def setup_scene(self, construct: bpy.types.Object) -> None:
        """Configure camera, lights, and world for card art."""
        pass

    def render(self, card_number: str) -> str:
        """
        Render card art.

        Returns:
            Filepath to rendered PNG.
        """
        pass

    def composite_card(self, render_path: str, card_data: dict) -> str:
        """
        Composite rendered art onto card template.

        Returns:
            Filepath to final card PNG.
        """
        pass
```

### 12.3 NetPExporter Class

```python
class NetPExporter:
    """Exports constructs to game engine formats."""

    SUPPORTED_FORMATS = ["gltf", "fbx", "obj", "alembic", "usd"]

    def __init__(self, output_dir: str):
        self.output_dir = Path(output_dir)

    def export(self, construct: bpy.types.Object, 
               card_number: str, fmt: str) -> str:
        """
        Export construct to specified format.

        Args:
            construct: Root object to export.
            card_number: Used for filename.
            fmt: One of SUPPORTED_FORMATS.

        Returns:
            Filepath to exported file.
        """
        pass

    def export_all(self, construct: bpy.types.Object, 
                   card_number: str) -> dict:
        """
        Export to all supported formats.

        Returns:
            Dictionary mapping format to filepath.
        """
        pass
```

---

## Appendix A: Quick Reference Card

```
┌─────────────────────────────────────────────────────────────┐
│  R3ALN3T.EXE BLENDER PROTOCOL v3.0 — QUICK REFERENCE      │
├─────────────────────────────────────────────────────────────┤
│  TIERS (16): OMEGA→ALPHA→BETA→GAMMA→DELTA→EPSILON→ZETA   │
│              →ETA→THETA→IOTA→KAPPA→LAMBDA→MU→NU→XI→OMICRON │
├─────────────────────────────────────────────────────────────┤
│  ALIGNMENTS (4): Mechanical | Viral | Angelic | Demonic     │
├─────────────────────────────────────────────────────────────┤
│  ELEMENTS (18): Fire Water Lightning Ice Wind Earth Light   │
│  Dark Void Metal Nature Sound Gravity Time Blood Poison     │
│  Crystal Plasma                                             │
├─────────────────────────────────────────────────────────────┤
│  BUILD:  blender --python netp_builder.py                   │
│  RENDER:  blender --python render_card.py                   │
│  EXPORT:  blender --python netp_exporter.py                 │
├─────────────────────────────────────────────────────────────┤
│  OMEGA tris: 100K  |  ALPHA: 70K  |  OMICRON: 1.5K        │
│  OMEGA emit: 12.0x |  OMICRON: 1.0x                        │
└─────────────────────────────────────────────────────────────┘
```

---

*Document generated for R3ALN3T.EXE v3.0*  
*Mythos Origin Hierarchy Compliant*  
*16 Ranks | 4 Alignments | 18 Elements*

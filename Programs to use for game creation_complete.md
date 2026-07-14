Got it — here's a battle-tested folder structure + file format cheat sheet so Blender ↔ UE5 ↔ GitHub plays nice and doesn't corrupt your 3026 project.

1. Master Folder Structure for Git + UE5 + Blender
Code
MyGame_3026/                  <- Git repo root
├── .gitignore               <- Use UE5 template + add *.blend
├── .gitattributes           <- Set up Git LFS here
├── README.md
│
├── /Project/                <- UE5 project lives here
│   ├── MyGame_3026.uproject
│   ├── /Config/
│   ├── /Content/
│   │   ├── /Characters/     <- uassets only
│   │   ├── /Environments/
│   │   │   ├── /City3026/   <- Megascans go here
│   │   │   └── /GridArena/  <- MMBN battle maps
│   │   ├── /UI/             <- UMG, chip icons from Krita
│   │   ├── /VFX/            <- Niagara systems
│   │   ├── /Audio/          <- .wav from Audacity
│   │   └── /Blueprints/
│   │       ├── /Systems/    <- GAS, GridManager for MMBN
│   │       └── /Camera/     <- Isometric cam BP
│   └── /Plugins/
│
├── /ArtSource/              <- NEVER put this in UE Content folder
│   ├── /Blender/            <- All .blend files live here
│   │   ├── /Characters/
│   │   │   ├── Hero_3026.blend
│   │   │   └── Hero_3026_Rigged.blend
│   │   ├── /Environments/
│   │   └── /Props/
│   ├── /Textures/           <- Source textures before UE import
│   │   ├── /Substance/      <- .sbs if you upgrade later
│   │   ├── /MaterialMaker/  <- .mmg files + exported PNGs
│   │   └── /Quixel/         <- Downloaded source from Bridge
│   ├── /Krita/              <- .kra files
│   │   ├── /UI/             <- Chip cards, HP bars
│   │   └── /ConceptArt/
│   └── /Mixamo/             <- Downloaded FBX anims before retarget
│
├── /AudioSource/            <- Audacity projects
│   ├── /SFX/                <- .aup3 files
│   └── /Music/
│
├── /Docs/                   <- GDD, MMBN chip balance sheets
└── /Builds/                 <- Packaged game, don't commit this

38 lines hidden
Key Rule: UE5 /Content/ only gets game-ready assets. Everything editable stays in /ArtSource/. Git tracks both, but LFS only tracks the big stuff.

2. .gitignore + .gitattributes for LFS
.gitignore - Start with Unreal's official template, then add:

Code
# Blender source files - keep but LFS them
*.blend1
*.blend2

# Audacity projects
*.aup3-shm
*.aup3-wal

# OS files
.DS_Store
Thumbs.db

# Never commit builds
/Builds/
/Saved/
/Intermediate/

11 lines hidden
.gitattributes - This is what saves your repo:

Code
# Unreal assets
*.uasset filter=lfs diff=lfs merge=lfs -text
*.umap filter=lfs diff=lfs merge=lfs -text

# Blender
*.blend filter=lfs diff=lfs merge=lfs -text

# Textures - anything >1MB
*.png filter=lfs diff=lfs merge=lfs -text
*.tga filter=lfs diff=lfs merge=lfs -text
*.exr filter=lfs diff=lfs merge=lfs -text
*.psd filter=lfs diff=lfs merge=lfs -text
*.kra filter=lfs diff=lfs merge=lfs -text

# Audio
*.wav filter=lfs diff=lfs merge=lfs -text
*.aup3 filter=lfs diff=lfs merge=lfs -text

# Meshes
*.fbx filter=lfs diff=lfs merge=lfs -text
*.obj filter=lfs diff=lfs merge=lfs -text

# Material Maker
*.mmg filter=lfs diff=lfs merge=lfs -text

19 lines hidden
Run git lfs install once after cloning. If you forget this, GitHub will reject pushes over 100MB.

3. File Format Pipeline: What to Export From Where
From → To

Use This Format

Settings That Matter

Avoid

Blender → UE5

.fbx

Scale: Apply All Transforms. Up Axis: Z, Forward: -Y. Check "Selected Objects". Smoothing: Face. Tangent Space: ON

.blend directly, .obj loses rig

Blender → UE5 Static Mesh

.fbx or .glb

Nanite enabled on import. LODs: let UE generate

N-gons, non-uniform scale

Blender → UE5 Skeletal

.fbx

Uncheck "Add Leaf Bones". Only deform bones. Bake Animation

Exporting whole scene

Mixamo → Blender → UE5

.fbx

Mixamo: FBX for Unity, no skin. Blender: retarget to UE mannequin, export FBX

Direct Mixamo → UE. Proportions break

Krita → UE5 UI

.png

RGBA, no compression. Power of 2 if tiling: 256, 512, 1024, 2048, 4096

.kra, .jpg for UI

Material Maker → UE5

.png or .tga

Export PBR set: Albedo, Normal, ORM/RMA, Emissive. 2K for world, 4K for hero

.mmg - UE can't read it

Quixel Bridge → UE5

Auto .uasset

Pick "Nanite" + "High" quality. Let Bridge handle it

Manual OBJ export

Audacity → UE5

.wav

16-bit, 44.1kHz for SFX. 24-bit for music. Mono for 3D sounds

.mp3 - UE re-encodes anyway

Blender → Mixamo

.fbx

T-pose, no animation, apply scale/rot, single mesh

A-pose, multiple objects

4. Blender → UE5 Export Checklist for 4K 3026 Assets
Scale: In Blender, set Unit Scale to 0.01, Length to Centimeters. 1m in Blender = 100 UU in UE5.
Apply Transforms: Ctrl+A → All Transforms before export. Non-uniform scale breaks collision.
UVs: Channel 0 = textures. Channel 1 = Lightmap UV. No overlapping in channel 1 or UE5 throws warnings.
Materials: Name them properly in Blender. M_City3026_Metal01 not Material.001. UE5 imports names.
Collision: Either make UCX_MeshName collision meshes in Blender, or use UE5 auto-convex. For your Diablo city, use "Use Complex as Simple" on Nanite meshes.
Origin: Put pivot at 0,0,0 in Blender. For props, bottom-center. For characters, feet.
5. MMBN Grid Battle Specific Notes
Your 6x3 grid tiles should be:

Model: Single 100x100x10cm plane in Blender → FBX
Material: Emissive grid lines made in Material Maker, exported as 2K PNG
Blueprint: One BP_GridTile actor in UE5 that instances the mesh. Don't import 18 separate meshes
Chips UI: Make 256x256 icons in Krita, save as PNG with alpha. Import to UE5 as User Interface 2D
6. What Breaks Most Often
Problem

Why It Happens

Fix

Mesh 100x too big in UE

Blender unit scale wrong

Set Blender to Metric, 0.01 scale, Apply Scale

Character distorted

Wrong bone roll or un-applied transforms

In Blender: Edit Mode → Select all → Alt+N → Recalculate Roll. Apply All Transforms

Textures look blurry at 4K

UE5 texture streaming default is 1K

Select texture → Change LOD Bias to 0, Max Texture Size to 4096

Git push rejected

Forgot Git LFS on .uasset

git lfs migrate import --include="*.uasset" then force push

Mixamo anims slide

Root motion not set

Enable Root Motion in UE5 anim sequence, or use in-place anims

Nanite mesh black

No UVs or bad normals

Blender: Recalculate Normals Outside, Add UV channel

more below:

1. Install Once
Download these 3:

Git: https://git-scm.com/downloads
Git LFS: https://git-lfs.github.com - run git lfs install once after installing
GitHub Desktop: https://desktop.github.com - easier than command line
2. Copy-Paste .gitignore
Make a new file called .gitignore in your Unreal project root and paste this. It ignores all the junk that breaks Git:

Code
# Unreal Engine Generated Folders
/Binaries/
/Build/
/DerivedDataCache/
/Intermediate/
/Saved/

# Visual Studio files
*.VC.db
*.opensdf
*.opendb
*.sdf
*.sln
*.suo
*.xcodeproj
*.xcworkspace

# OS files
.DS_Store
Thumbs.db

# Blender temp files
*.blend1
*.blend2

# Don't ignore these UE folders
!/Content/**/
!/Config/**/
!/Source/**/

# But ignore auto-generated stuff inside Content
Content/Developers/
Content/Collections/

28 lines hidden
3. Copy-Paste Git LFS Setup
Open Git Bash / Terminal in your project folder and run these once:

Bash
git lfs install
git lfs track "*.uasset"
git lfs track "*.umap"
git lfs track "*.fbx"
git lfs track "*.blend"
git lfs track "*.png"
git lfs track "*.tga"
git lfs track "*.wav"
git lfs track "*.mp3"
git add .gitattributes

5 lines hidden
That tells Git: "Don't try to cram these huge files into the normal repo. Use LFS instead."

4. The "No Brain" Workflow with GitHub Desktop
Create repo: GitHub Desktop → File → New Repository → pick your UE5 project folder
First commit: It'll auto-use your .gitignore + .gitattributes. Commit message: Initial commit
Push to GitHub: Click "Publish repository" → uncheck "Keep this code private" if you want it public
Daily work:
Make changes in UE5/Blender
Open GitHub Desktop → it'll show all changed files
Summary: Added MMBN grid system → Commit → Push
Why This = Less Hard Work
Without this

With this setup

GitHub rejects push: "File too large"

LFS handles 2GB.uassets no problem

Repo becomes 50GB+ and dies

Only code + small files in main repo

DerivedDataCache corrupts for teammates

.gitignore blocks it completely

You accidentally commit 5000 temp files

.gitignore filters them out

more below:

*IMPORTANT NOTE OT TAKE 

Are source files separate from UE assets? /ArtSource vs /Content so Git LFS doesn’t explode
Is your MMBN battle stuff isolated? Easier to iterate on the grid system if it’s /Content/BattleSystem/ not mixed with open world
Where are 4K textures going? They’ll nuke performance if they’re not in their own /Textures_4K folder with LOD groups
Can 2 people work without conflicts? Blueprints + levels in separate folders prevents merge hell
Any naming landmines? Spaces, special chars, or NewMaterial breaks imports fast

MORE BELOW:

API's 

https://github.com/cporter202/API-mega-list





#!/usr/bin/env python3
# Builds + saves Content/Maps/Rotterdam_PoC.umap via UE editor Python.
# Gap A deliverable from Europe_Vertical_Slice.md: player start, walkable plaza, encounter zone.
import unreal, os

LOG = r"C:\Users\richa\Desktop\R3ALN3T_UE5\Scripts\rotterdam_build.log"
def log(s):
    with open(LOG, "a") as f: f.write(s + "\n")
    unreal.log(s)

log("=== Rotterdam_PoC builder start ===")

# 1) New empty level
ell = unreal.EditorLevelLibrary
world = ell.get_editor_world()
log("editor world: %s" % (world.get_path_name() if world else "NONE"))

# 2) Floor (Lifted Plate plaza) - large flat cube
cube = unreal.load_asset("/Engine/BasicShapes/Cube.Cube")
sma_cls = unreal.StaticMeshActor
floor = ell.spawn_actor_from_class(sma_cls, unreal.Vector(0,0,-50))
floor.static_mesh_component.set_static_mesh(cube)
floor.set_actor_scale3d(unreal.Vector(40, 40, 1))  # 400x400x10 unit plate
floor.set_actor_label("Rotterdam_Plate_Floor")
log("floor spawned")

# 3) PlayerStart
ps = ell.spawn_actor_from_class(unreal.PlayerStart, unreal.Vector(0,0,100))
ps.set_actor_label("PlayerStart_Rotterdam")
log("playerstart spawned")

# 4) Plaza props - Lifted Plate skyline (canon: drowned twin, Dam-Spine rail)
for i,(x,y) in enumerate([(-600,-600),(600,-600),(-600,600),(600,600),(0,-900)]):
    b = ell.spawn_actor_from_class(sma_cls, unreal.Vector(x,y,200))
    b.static_mesh_component.set_static_mesh(cube)
    b.set_actor_scale3d(unreal.Vector(4,4,40))
    b.set_actor_label("PlateTower_%d" % i)
log("5 towers spawned")

# 5) Encounter trigger volume (Gap A: one encounter zone)
tb = ell.spawn_actor_from_class(unreal.TriggerBox, unreal.Vector(300,0,100))
tb.set_actor_scale3d(unreal.Vector(4,4,4))
tb.set_actor_label("EncounterZone_Rotterdam")
log("encounter trigger spawned")

# 6) Up-Link node (Gap E: one travel node stub)
ul = ell.spawn_actor_from_class(sma_cls, unreal.Vector(-900,0,200))
ul.static_mesh_component.set_static_mesh(cube)
ul.set_actor_scale3d(unreal.Vector(3,3,30))
ul.set_actor_label("AscentUpLink_Node")
log("uplink node spawned")

# 7) Save as /Game/Maps/Rotterdam_PoC
out = "/Game/Maps/Rotterdam_PoC"
unreal.EditorLoadingAndSavingUtils.save_map(world, out)
log("SAVED level to %s" % out)
log("=== Rotterdam_PoC builder done ===")

# build_graybox_map.py  — persist Gap A gray-box level for PIE/-game runtime.
import unreal, os
log = lambda m: unreal.log("[GRAYBOX] " + str(m))

MAP = "/Game/Maps/GrayBox_Test"
DISK = "C:/Users/richa/Desktop/R3ALN3T_UE5/Project/R3ALN3T_UE5/Content/Maps/GrayBox_Test.umap"

# Hard delete disk + asset-lib entry.
if os.path.exists(DISK):
    os.remove(DISK); log("deleted disk umap")
if unreal.EditorAssetLibrary.does_asset_exist(MAP):
    unreal.EditorAssetLibrary.delete_asset(MAP); log("deleted asset-lib entry")

# Create a brand-new level via the Level Editor Subsystem (returns the UWorld).
les = unreal.get_editor_subsystem(unreal.LevelEditorSubsystem)
world = les.new_level(MAP)
log("new_level -> " + str(world))

# Floor: engine cube scaled flat + collision.
floor = unreal.EditorLevelLibrary.spawn_actor_from_class(
    unreal.StaticMeshActor, unreal.Vector(0, 0, -50))
floor.static_mesh_component.set_static_mesh(
    unreal.load_asset("/Engine/BasicShapes/Cube.Cube"))
floor.set_actor_scale3d(unreal.Vector(200.0, 200.0, 1.0))
floor.static_mesh_component.set_collision_enabled(
    unreal.CollisionEnabled.QUERY_AND_PHYSICS)
floor.static_mesh_component.set_collision_profile_name("BlockAll")
log("floor placed + collision")

unreal.EditorLevelLibrary.spawn_actor_from_class(
    unreal.PlayerStart, unreal.Vector(0, 0, 100))
log("playerstart placed")

unreal.EditorLevelLibrary.spawn_actor_from_class(
    unreal.GrayBoxPlayerPawn, unreal.Vector(0, 0, 100))
log("GrayBoxPlayerPawn placed (autopossess + autotest)")

# Save via EditorLoadingAndSavingUtils.
ok = unreal.EditorLoadingAndSavingUtils.save_map(world, MAP)
log("save_map -> " + str(ok))
# Re-confirm on disk.
import time; time.sleep(1)
log("disk exists -> " + str(os.path.exists(DISK)))

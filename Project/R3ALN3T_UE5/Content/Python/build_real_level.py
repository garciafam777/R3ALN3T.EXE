# build_real_level.py — create a FRESH-named level (no phantom entry) WITH actors, save, verify.
import unreal, os, traceback

MAP = "/Game/Maps/GrayBox_Test2"   # fresh path: no phantom registry entry
DEBUG = "C:/Users/richa/Desktop/R3ALN3T_UE5/Project/R3ALN3T_UE5/Saved/Logs/realmap_debug.txt"
def D(m):
    with open(DEBUG, "a") as f: f.write(str(m) + "\n")
def L(m):
    unreal.log("[REALMAP] " + str(m)); D(m)

D("\n=== run " + __import__('datetime').datetime.now().isoformat() + " (fresh path) ===")
try:
    r = unreal.EditorLevelLibrary.new_level(MAP)
    L("new_level(" + MAP + ") returned: " + str(r))

    floor = unreal.EditorLevelLibrary.spawn_actor_from_class(
        unreal.StaticMeshActor, unreal.Vector(0.0, 0.0, -50.0))
    floor.static_mesh_component.set_static_mesh(unreal.load_asset("/Engine/BasicShapes/Cube.Cube"))
    floor.set_actor_scale3d(unreal.Vector(200.0, 200.0, 1.0))
    floor.static_mesh_component.set_collision_enabled(unreal.CollisionEnabled.QUERY_AND_PHYSICS)
    floor.static_mesh_component.set_collision_profile_name("BlockAll")
    L("floor placed")

    ps = unreal.EditorLevelLibrary.spawn_actor_from_class(unreal.PlayerStart, unreal.Vector(0.0, 0.0, 0.0))
    L("playerstart placed: " + str(ps is not None))

    pawn = unreal.EditorLevelLibrary.spawn_actor_from_class(unreal.GrayBoxPlayerPawn, unreal.Vector(0.0, 0.0, 100.0))
    L("graybox pawn placed: " + str(pawn is not None))

    unreal.EditorLevelLibrary.save_current_level()
    L("save_current_level() called")

    unreal.EditorLevelLibrary.load_level(MAP)
    actors = unreal.EditorLevelLibrary.get_all_level_actors()
    kinds = [a.get_class().get_name() for a in actors]
    L("actor count after reload: " + str(len(actors)) + " classes: " + str(kinds))

    disk = "C:/Users/richa/Desktop/R3ALN3T_UE5/Project/R3ALN3T_UE5/Content/Maps/GrayBox_Test2.umap"
    L("disk exists: " + str(os.path.exists(disk)) + " size=" + str(os.path.getsize(disk) if os.path.exists(disk) else -1))
except Exception as e:
    L("EXCEPTION: " + repr(e))
    D(traceback.format_exc())

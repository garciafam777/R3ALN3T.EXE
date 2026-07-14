# pie_runtime.py — spawn + simulate, then RETURN (no blocking sleep).
# In headless -ExecutePythonScript the editor keeps ticking after the script returns,
# so the pawn's C++ BeginPlay + 0.3s autotest timer fire on real ticks.
# The shell sleeps separately (doesn't block UE) before grepping the log.
import unreal
log = lambda m: unreal.log("[PIERUN] " + str(m))

floor = unreal.EditorLevelLibrary.spawn_actor_from_class(
    unreal.StaticMeshActor, unreal.Vector(0,0,-50))
floor.static_mesh_component.set_static_mesh(unreal.load_asset("/Engine/BasicShapes/Cube.Cube"))
floor.set_actor_scale3d(unreal.Vector(200.0,200.0,1.0))
floor.static_mesh_component.set_collision_enabled(unreal.CollisionEnabled.QUERY_AND_PHYSICS)
floor.static_mesh_component.set_collision_profile_name("BlockAll")
log("floor placed")
pawn = unreal.EditorLevelLibrary.spawn_actor_from_class(
    unreal.GrayBoxPlayerPawn, unreal.Vector(0,0,100))
log("pawn spawned: " + str(pawn is not None))

unreal.EditorLevelLibrary.editor_play_simulate()
log("simulate started — pawn BeginPlay + 0.3s autotest will fire on live ticks; script returns, editor keeps running")
# NOTE: no time.sleep here. Returning lets UE's own loop tick.

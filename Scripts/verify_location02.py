# verify_location02.py
# Track 4: confirm Location02.umap loads cleanly and carries the BattleGridManager + roster wiring.
import unreal, os
MAP = "/Game/R3ALN3T/Maps/Location02"
print(f"[loc2] loading {MAP} ...")
ok = unreal.EditorLevelLibrary.load_level(MAP)
print(f"[loc2] load_level returned: {ok}")
# confirm BattleGridManager actor present in the loaded level
world = unreal.EditorLevelLibrary.get_editor_world()
actors = unreal.EditorLevelLibrary.get_all_level_actors()
grid = [a for a in actors if a.get_class().get_name() == "BattleGridManager"]
print(f"[loc2] actors in level: {len(actors)}, BattleGridManager found: {len(grid)}")
# ConstructRoster DT still resolves (roster system inherited verbatim)
dt = unreal.EditorAssetLibrary.load_asset("/Game/R3ALN3T/Battle/ConstructRoster")
print(f"[loc2] ConstructRoster DT loaded: {dt is not None}")
print("[loc2] VERIFY DONE")
unreal.SystemLibrary.quit_editor()

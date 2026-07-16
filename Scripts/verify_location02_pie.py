# verify_location02_pie.py
# Track 4: load Location02, force auto-fire CVar, run PIE, confirm seam fires (3 NetPs placed).
import unreal, time
MAP = "/Game/R3ALN3T/Maps/Location02"
unreal.EditorLevelLibrary.load_level(MAP)
# force the golden-loop CVar on
unreal.SystemLibrary.execute_console_command(None, "r3alnet.AutoFireGoldenLoop 1")
# kick PIE in-editor
unreal.EditorLevelLibrary.editor_play_simulate()  # simulate-mode: ticks world + BeginPlay
time.sleep(6)
# inspect log via the running editor's output (we grep disk after quit)
print("[loc2-pie] PIE started, sleeping for seam")
time.sleep(4)
unreal.EditorLevelLibrary.editor_end_play() if hasattr(unreal.EditorLevelLibrary,"editor_end_play") else None
print("[loc2-pie] DONE")
unreal.SystemLibrary.quit_editor()

# import_card_frames.py  (UE5.8-correct AssetImportTask field-assignment)
# Track 3: import 21 generated card-frame PNGs as Texture2D into /Game/R3ALN3T/TCG/CardFrames/
import unreal, os

SRC = r"C:\Users\richa\Desktop\R3ALN3T_UE5\Scripts\gen_card_frames"
DEST = "/Game/R3ALN3T/TCG/CardFrames"

tasks = []
for fn in os.listdir(SRC):
    if not fn.lower().endswith(".png"):
        continue
    t = unreal.AssetImportTask()
    t.filename = os.path.join(SRC, fn).replace("\\", "/")
    t.destination_path = DEST
    t.destination_name = fn.rsplit(".", 1)[0]   # fire_frame.png -> fire_frame
    t.replace_existing = False
    t.automated = True
    tasks.append(t)

unreal.EditorAssetLibrary.make_directory(DEST)
print(f"[frames] {len(tasks)} png tasks -> {DEST}")
unreal.AssetToolsHelpers.get_asset_tools().import_asset_tasks(tasks)

ok = 0
missing = []
for t in tasks:
    full = f"{t.destination_path}/{t.destination_name}"
    if unreal.EditorAssetLibrary.does_asset_exist(full):
        ok += 1
    else:
        missing.append(full)
print(f"[frames] DONE: {ok}/{len(tasks)} imported")
for m in missing:
    print("  MISSING:", m)

# persist to disk (headless runs skip the normal save pass)
saved = 0
for t in tasks:
    full = f"{t.destination_path}/{t.destination_name}"
    if unreal.EditorAssetLibrary.does_asset_exist(full):
        if unreal.EditorAssetLibrary.save_asset(full, False):
            saved += 1
print(f"[frames] SAVED {saved}/{len(tasks)} to disk")
unreal.SystemLibrary.quit_editor()

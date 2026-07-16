# import_music_tracks.py  (UE5.8-correct: AssetImportTask takes no kwarg ctor)
# Track 5: import space/angelic/hell_map wavs into /Game/R3ALN3T/Audio/Music/{Space,Angelic,Hell}
import unreal, os

SRC = {
    "Space":   r"C:\Users\richa\Downloads\space_music",
    "Angelic": r"C:\Users\richa\Downloads\angelic_music",
    "Hell":    r"C:\Users\richa\Downloads\hell_map_music",
}
DEST = "/Game/R3ALN3T/Audio/Music"

def sanitize(name: str) -> str:
    base = name.rsplit(".", 1)[0]
    out = []
    for ch in base:
        out.append("_" if (ch in " ()-'") else ch)
    s = "".join(out).strip("_")
    while "__" in s:
        s = s.replace("__", "_")
    return s or "Track"

tasks = []
made_dirs = set()
for sub, src in SRC.items():
    dest_dir = f"{DEST}/{sub}"
    made_dirs.add(dest_dir)
    for fn in os.listdir(src):
        if not fn.lower().endswith(".wav"):
            continue
        t = unreal.AssetImportTask()
        t.filename = os.path.join(src, fn).replace("\\", "/")
        t.destination_path = dest_dir
        t.destination_name = sanitize(fn)
        t.replace_existing = False
        t.automated = True
        tasks.append(t)

for d in made_dirs:
    unreal.EditorAssetLibrary.make_directory(d)

print(f"[import] {len(tasks)} wav tasks across {len(made_dirs)} folders")
unreal.AssetToolsHelpers.get_asset_tools().import_asset_tasks(tasks)

ok = 0
missing = []
for t in tasks:
    full = f"{t.destination_path}/{t.destination_name}"
    if unreal.EditorAssetLibrary.does_asset_exist(full):
        ok += 1
    else:
        missing.append(full)
print(f"[import] DONE: {ok}/{len(tasks)} imported successfully")
for m in missing:
    print("  MISSING:", m)

# Persist each imported asset to disk explicitly (headless runs skip the normal save pass)
print("[import] saving imported assets to disk...")
saved = 0
for t in tasks:
    full = f"{t.destination_path}/{t.destination_name}"
    if unreal.EditorAssetLibrary.does_asset_exist(full):
        if unreal.EditorAssetLibrary.save_asset(full, False):
            saved += 1
print(f"[import] SAVED {saved}/{len(tasks)} to disk")

# Graceful exit so the save flush completes before the process dies
unreal.SystemLibrary.quit_editor()

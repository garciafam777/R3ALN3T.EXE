# create_layer_levels.py -- deterministic layer-sublevel creation (Area-1 fix)
# Run via: UnrealEditor <project> -ExecutePythonScript=<this> -unattended -nopause
# Creates empty, saved .umap packages matching WorldLayerManager's LevelName entries
# so TeleportToLayer / streaming has real targets instead of an empty array.
import unreal

LAYERS = [
    "/Game/R3ALN3T/Maps/Layers/L_Heaven",
    "/Game/R3ALN3T/Maps/Layers/L_Hell",
    "/Game/R3ALN3T/Maps/Layers/L_Cyberspace",
    "/Game/R3ALN3T/Maps/Layers/L_OuterSpace",
]

def create_level(pkg):
    # Returns existing or creates+saves a minimal world.
    if unreal.EditorAssetLibrary.does_asset_exist(pkg):
        print(f"[layer] exists: {pkg}")
        return True
    # Create a new world asset (empty level).
    world = unreal.EditorLevelLibrary.new_level(pkg)
    if world is None:
        # fallback: create a World factory asset directly
        factory = unreal.WorldFactory()
        asset_tools = unreal.AssetToolsHelpers.get_asset_tools()
        world = asset_tools.create_asset(
            pkg.split("/")[-1], "/".join(pkg.split("/")[:-1]), unreal.World, factory
        )
    if world is None:
        print(f"[layer] FAILED to create: {pkg}")
        return False
    # Save the package.
    ok = unreal.EditorAssetLibrary.save_asset(pkg, only_if_is_dirty=False)
    print(f"[layer] created+saved: {pkg} (save_ok={ok})")
    return ok

if __name__ == "__main__":
    for p in LAYERS:
        create_level(p)
    print("[layer] DONE")

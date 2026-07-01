# Step4_Enforce_Asset_Import_Rules.md
## Task 3: Enforce Asset Import Rules & Core Configuration Setup

Pinokio must append these variables inside [PROJECT_ROOT]/Config/DefaultEngine.ini:
[/Script/Engine.RendererSettings]
r.Nanite=1
r.Nanite.AllowCompress=1
r.RuntimeVirtualTextures=1

[/Script/UnrealEd.FbxImportUI]
bCreateCollision=True
bImportAsDynamicType=False
bAutoComputeLodDistances=True

### Script: [PROJECT_ROOT]/Build/Apply_Engine_Import_Rules.py
import unreal
def enforce_asset_optimization(target_folder):
    asset_registry = unreal.AssetRegistryHelpers.get_asset_registry()
    asset_data_list = asset_registry.get_assets_by_path(target_folder, recursive=True)
    for asset_data in asset_data_list:
        if asset_data.asset_class_path.asset_name == 'StaticMesh':
            mesh = asset_data.get_asset()
            if mesh:
                mesh.get_editor_property("body_setup").set_editor_property("collision_complexity", unreal.CollisionComplexity.CTF_USE_COMPLEX_AS_SIMPLE)
                nanite_settings = unreal.NaniteSettings()
                nanite_settings.set_editor_property("b_enabled", True)
                mesh.set_editor_property("nanite_settings", nanite_settings)
                unreal.EditorStaticMeshLibrary.rebuild_mesh(mesh)
                unreal.EditorAssetLibrary.save_loaded_asset(mesh)
if __name__ == "__main__":
    enforce_asset_optimization("/Game/R3ALN3T/Environments")

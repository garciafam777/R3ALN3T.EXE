# Step5_Production_Pipeline_And_Asset_Registry.md
## Production Pipeline & Asset Registry Trackers

### Script: [PROJECT_ROOT]/Build/Apply_Production_Registry_Audit.py
import unreal, os, json
def run_global_production_audit(target_root_path, output_report_json):
    asset_registry = unreal.AssetRegistryHelpers.get_asset_registry()
    asset_list = asset_registry.get_assets_by_path(target_root_path, recursive=True)
    audit_report = {"summary": {"total_scanned": len(asset_list), "passed": 0, "failed": 0}, "flagged_assets": []}
    
    for asset_data in asset_list:
        asset_name = str(asset_data.asset_name)
        asset_class = asset_data.asset_class_path.asset_name
        has_error = False
        
        if asset_class == 'StaticMesh' and not asset_name.startswith("SM_"): has_error = True
        elif asset_class == 'Texture2D' and not asset_name.startswith("T_"): has_error = True
        elif asset_class == 'MaterialInstanceConstant' and not asset_name.startswith("MI_"): has_error = True
        
        if has_error: audit_report["summary"]["failed"] += 1
        else: audit_report["summary"]["passed"] += 1
            
    with open(output_report_json, 'w', encoding='utf-8') as f:
        json.dump(audit_report, f, indent=4)

if __name__ == "__main__":
    project_build_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "Build"))
    run_global_production_audit("/Game/R3ALN3T/Environments", os.path.join(project_build_dir, "Asset_Registry_Audit_Report.json"))

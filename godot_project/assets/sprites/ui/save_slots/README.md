# Save Slot Thumbnails

Optional PNG thumbnails for the load picker. Upload from your UI layout workstation when ready.

## Naming convention

| File | Usage |
|------|-------|
| `slot_01.png` … `slot_10.png` | Per-slot thumbnail (matches save slot index) |
| `default.png` | Fallback when no slot-specific image exists |

## Resolution

- Recommended: **128×128** or **256×256** PNG
- UI scales automatically in the load picker

## Custom path per save

Set `thumbnail_path` in save metadata (via `GameSaveManager.update_slot_preview`) to point at any `res://` texture.

## Location

Place files in this folder:

`godot_project/assets/sprites/ui/save_slots/`

Godot will pick them up automatically on the next project refresh.

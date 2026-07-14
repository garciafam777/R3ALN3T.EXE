#!/usr/bin/env python3
"""
Chronos (A_Team) — scriptable asset gap-fix for R3ALN3T.EXE finishing steps.

Closes integration/wiring gaps that are SCRIPTABLE (no engine compile needed):
  1. Rename old-name card frames to locked canon 21:
       water_frame.png      -> aqua_frame.png
       lightning_frame.png  -> elec_frame.png
       thunder_frame.png    -> elec_alt_frame.png   (Elec variant spelling)
       venom_frame.png      -> poison_frame.png
  2. Generate placeholder card frames for the 3 canon-21 elements with NO frame:
       Wood, Null, Glitch  (final 1536x2752 portrait format, matching existing frames).
  3. Generate Trinity.png placeholder (3rd Construct art; Eternity/Tyranny exist).

All outputs are PLACEHOLDERS flagged for Echo to replace with final 4K art.
No engine code is touched. Re-runnable / idempotent.
"""
import json, os, glob, shutil
from pathlib import Path
from datetime import datetime, timezone
from PIL import Image, ImageDraw, ImageFont

ROOT = Path(__file__).resolve().parents[2]   # repo root
FRAME_DIR = ROOT / "Assets/Images/UI/card_frames"
NETP_DIR = ROOT / "Assets/Images/NetP"

# Element accent colors (canon 21) for placeholder styling
ELEMENT_COLORS = {
    'Fire': (230, 70, 30), 'Aqua': (30, 140, 220), 'Elec': (240, 220, 40),
    'Ice': (150, 220, 255), 'Wind': (120, 220, 160), 'Earth': (150, 110, 60),
    'Light': (245, 240, 200), 'Dark': (40, 30, 60), 'Void': (90, 40, 120),
    'Metal': (180, 185, 195), 'Nature': (90, 180, 70), 'Sound': (220, 120, 200),
    'Gravity': (110, 110, 130), 'Time': (200, 180, 90), 'Blood': (180, 30, 40),
    'Poison': (140, 200, 50), 'Crystal': (170, 240, 255), 'Plasma': (255, 120, 200),
    'Wood': (110, 150, 60), 'Null': (60, 60, 70), 'Glitch': (0, 255, 180),
}

FW, FH = 1536, 2752  # existing finalized frame resolution (portrait)

log_lines = []

def ts():
    return datetime.now(timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ")

def _font(size):
    for cand in ["C:/Windows/Fonts/arial.ttf", "C:/Windows/Fonts/arialbd.ttf",
                 "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf"]:
        if os.path.exists(cand):
            return ImageFont.truetype(cand, size)
    return ImageFont.load_default()

def make_placeholder_frame(name, color, label):
    out = FRAME_DIR / f"{name}_frame.png"
    img = Image.new("RGB", (FW, FH), (18, 18, 22))
    d = ImageDraw.Draw(img)
    # border
    d.rectangle([40, 40, FW - 40, FH - 40], outline=color, width=24)
    d.rectangle([80, 80, FW - 80, FH - 80], outline=tuple(min(255, c + 40) for c in color), width=6)
    # center swatch
    cx, cy = FW // 2, FH // 2
    d.ellipse([cx - 320, cy - 320, cx + 320, cy + 320], fill=color)
    # labels
    f_big = _font(180)
    d.text((cx, cy - 60), label, fill=(10, 10, 12), font=f_big, anchor="mm")
    f_small = _font(70)
    d.text((FW // 2, FH - 220), "PLACEHOLDER - replace w/ 4K", fill=(220, 220, 220),
           font=f_small, anchor="mm")
    d.text((FW // 2, 140), "R3ALN3T.EXE", fill=(200, 200, 200), font=f_small, anchor="mm")
    img.save(out)
    log_lines.append(f"  + generated {out.name} ({FW}x{FH}, elem={label})")
    return out

def make_construct(name, color):
    out = NETP_DIR / f"{name}.png"
    W, H = 1024, 1536  # match existing Eternity/Tyranny resolution
    img = Image.new("RGB", (W, H), (16, 16, 20))
    d = ImageDraw.Draw(img)
    d.rectangle([30, 30, W - 30, H - 30], outline=color, width=20)
    cx, cy = W // 2, int(H * 0.42)
    d.ellipse([cx - 260, cy - 260, cx + 260, cy + 260], fill=color)
    d.text((cx, cy), name[0], fill=(10, 10, 12), font=_font(360), anchor="mm")
    f = _font(90)
    d.text((W // 2, H - 180), name.upper(), fill=(230, 230, 230), font=f, anchor="mm")
    d.text((W // 2, H - 90), "PLACEHOLDER - replace w/ 4K", fill=(200, 200, 200),
           font=_font(48), anchor="mm")
    img.save(out)
    log_lines.append(f"  + generated {out.name} ({W}x{H})")
    return out

def main():
    log_lines.append(f"[{ts()}] Chronos placeholder-gen start (scriptable asset gaps)")
    # --- 1. rename old-name frames ---
    renames = [
        ("water_frame.png", "aqua_frame.png", "Water->Aqua (canon)"),
        ("lightning_frame.png", "elec_frame.png", "Lightning->Elec (canon)"),
        ("thunder_frame.png", "elec_alt_frame.png", "Thunder->Elec variant (canon)"),
        ("venom_frame.png", "poison_frame.png", "Venom->Poison (canon)"),
    ]
    for src, dst, note in renames:
        s = FRAME_DIR / src
        if s.exists():
            t = FRAME_DIR / dst
            if not t.exists():
                shutil.move(str(s), str(t))
                log_lines.append(f"  ~ renamed {src} -> {dst} ({note})")
            else:
                log_lines.append(f"  = skip {src} (target {dst} already exists)")
        else:
            log_lines.append(f"  - absent {src} (nothing to do)")

    # --- 2. generate missing element frames (Wood / Null / Glitch) ---
    for elem in ["Wood", "Null", "Glitch"]:
        if not (FRAME_DIR / f"{elem.lower()}_frame.png").exists():
            make_placeholder_frame(elem.lower(), ELEMENT_COLORS[elem], elem)
        else:
            log_lines.append(f"  = {elem.lower()}_frame.png already present")

    # --- 3. generate Trinity.png (3rd Construct) ---
    if not (NETP_DIR / "Trinity.png").exists():
        make_construct("Trinity", ELEMENT_COLORS['Void'])
    else:
        log_lines.append("  = Trinity.png already present")

    summary = {
        "generated_at": ts(),
        "author": "Chronos (A_Team)",
        "action": "scriptable placeholder asset gap-fix",
        "renames": [r[1] for r in renames],
        "generated_frames": ["wood_frame.png", "null_frame.png", "glitch_frame.png"],
        "generated_construct": ["Trinity.png"],
        "note": "PLACEHOLDERS only — Echo lane to replace with final 4K art. Engine not required.",
    }
    (ROOT / "Scripts/placeholder_gen/run_log.json").write_text(json.dumps(summary, indent=2))
    log_lines.insert(0, json.dumps(summary))
    outpath = ROOT / "Scripts/placeholder_gen/last_run.txt"
    outpath.write_text("\n".join(log_lines) + "\n")
    print("\n".join(log_lines))

if __name__ == "__main__":
    main()

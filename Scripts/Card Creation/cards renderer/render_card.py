import os
import csv
import re
from PIL import Image, ImageDraw, ImageFont

# --- EXACT DIRECTORY PATH CONSTRAINTS ---
CSV_PATH = r"C:\Users\richa\Desktop\R3ALN3T.EXE\Card Creation\cards\generated_cards.csv"
OUTPUT_DIR = r"C:\Users\richa\Desktop\R3ALN3T.EXE\Card Creation\cards\Rendered_Output"
ASSETS_DIR = r"C:\Users\richa\Desktop\R3ALN3T.EXE\Card Creation\cards renderer\assets"

os.makedirs(OUTPUT_DIR, exist_ok=True)

# Translation map between data names and your asset filenames
ELEMENT_ASSET_MAP = {
    "lightning": "thunder",
    "poison": "venom"
}

def sanitize_filename(filename):
    """Strips out illegal Windows filename characters."""
    return re.sub(r'[\\/*?:"<>|]', "", filename)

def get_element_from_class(construct_class):
    """Extracts element from string format: 'TAU-RANK [WIND] NetP'"""
    try:
        elem = construct_class.split('[')[1].split(']')[0].strip().lower()
        # Translate to match actual filename if needed (e.g., lightning -> thunder)
        return ELEMENT_ASSET_MAP.get(elem, elem)
    except IndexError:
        return "void"

def render_all_cards():
    if not os.path.exists(CSV_PATH):
        print(f"[-] Target missing: {CSV_PATH}")
        return

    # Load your exact font file from assets
    font_path = os.path.join(ASSETS_DIR, "Fonts", "Consolas-Bold.ttf")
    if os.path.exists(font_path):
        font_main = ImageFont.truetype(font_path, 28)
        font_sub = ImageFont.truetype(font_path, 20)
    else:
        print("[!] Consolas-Bold.ttf not found in assets, defaulting to system font.")
        font_main = ImageFont.load_default()
        font_sub = ImageFont.load_default()

    with open(CSV_PATH, mode='r', encoding='utf-8') as f:
        reader = csv.DictReader(f)
        
        for row in reader:
            card_name = row["Name"]
            card_num = row["Card Number"].split(' - ')[0]
            element = get_element_from_class(row["Construct Class"])
            
            print(f"[+] Layering Frame Assets: {card_num} - {card_name} [{element.upper()}]")

            # 1. LOAD THE MATCHING ELEMENT FRAME
            frame_path = os.path.join(ASSETS_DIR, "frames", f"{element}_frame.png")
            
            if not os.path.exists(frame_path):
                print(f"    [!] Missing frame asset: {frame_path}. Using fallback background.")
                base_card = Image.new("RGBA", (1200, 1800), (15, 8, 41, 255))
            else:
                base_card = Image.open(frame_path).convert("RGBA")

            canvas = ImageDraw.Draw(base_card)

            # 2. STAMP ELEMENT ICON
            # Map elements back to icon names if they use the map (e.g. thunder frame uses lightning icon)
            icon_file_name = "lightning" if element == "thunder" else ("poison" if element == "venom" else element)
            icon_path = os.path.join(ASSETS_DIR, "element_icons", f"{icon_file_name}.png")
            if os.path.exists(icon_path):
                icon_img = Image.open(icon_path).convert("RGBA")
                icon_img = icon_img.resize((48, 48))
                base_card.paste(icon_img, (50, 42), icon_img)

            # 3. TYPOGRAPHY TEXT LAYERS
            # Adjust these X, Y coordinates to target your frame design text-boxes exactly
            canvas.text((120, 50), row["Name"], fill="#E9D5FF", font=font_main)
            canvas.text((60, 110), row["Construct Class"], fill="#A855F7", font=font_sub)
            canvas.text((60, 1350), row["Core Stats"], fill="#A7F3D0", font=font_sub)
            canvas.text((920, 50), row["Card Number"], fill="#7C3AED", font=font_sub)

            # 4. EXPORT COMPLETED COMPOSITE
            raw_filename = f"{card_num}_{row['Code']}.png"
            clean_filename = sanitize_filename(raw_filename)
            
            final_output_path = os.path.join(OUTPUT_DIR, clean_filename)
            base_card.save(final_output_path, "PNG")

    print(f"\n[!] Success! All compiled cards exported to:\n{OUTPUT_DIR}")

if __name__ == "__main__":
    render_all_cards()
import os
import csv
import json
import textwrap
from PIL import Image, ImageDraw, ImageFont, ImageFilter
import numpy as np
from typing import Dict, List, Tuple, Optional

# ======================
# CONFIGURATION
# ======================
CSV_PATH = "cards.csv"  # Path to your CSV
OUTPUT_DIR = "output_cards"  # Where to save generated cards
ASSETS_DIR = "assets"  # For character art (optional)
CARD_SIZE = (1080, 1500)  # Width, Height (matches your example)
FONT_DIR = "fonts"  # Place .ttf files here (or use defaults)

# Element color mapping (from your roster)
ELEMENT_COLORS = {
    "Fire":      {"primary": "#FF4500", "secondary": "#FF8C00", "accent": "#FFD700", "glow": "#FF6347"},
    "Water":     {"primary": "#1E90FF", "secondary": "#00BFFF", "accent": "#87CEEB", "glow": "#4169E1"},
    "Lightning": {"primary": "#FFD700", "secondary": "#FFA500", "accent": "#FFE4B5", "glow": "#FFD700"},
    "Ice":       {"primary": "#00FFFF", "secondary": "#87CEEB", "accent": "#ADD8E6", "glow": "#00BFFF"},
    "Wind":      {"primary": "#90EE90", "secondary": "#00FA9A", "accent": "#98FB98", "glow": "#7FFF00"},
    "Earth":     {"primary": "#8B4513", "secondary": "#A0522D", "accent": "#CD853F", "glow": "#D2691E"},
    "Light":     {"primary": "#FFFF00", "secondary": "#FFD700", "accent": "#FFFFFF", "glow": "#FFE4B5"},
    "Dark":      {"primary": "#4B0082", "secondary": "#800080", "accent": "#000000", "glow": "#9400D3"},
    "Void":      {"primary": "#2F4F4F", "secondary": "#000000", "accent": "#4B0082", "glow": "#1E0A3C"},
    "Metal":     {"primary": "#C0C0C0", "secondary": "#808080", "accent": "#A9A9A9", "glow": "#D3D3D3"},
    "Nature":    {"primary": "#228B22", "secondary": "#006400", "accent": "#32CD32", "glow": "#7CFC00"},
    "Sound":     {"primary": "#9370DB", "secondary": "#BA55D3", "accent": "#9932CC", "glow": "#8A2BE2"},
    "Gravity":   {"primary": "#000080", "secondary": "#191970", "accent": "#000000", "glow": "#483D8B"},
    "Time":      {"primary": "#FFD700", "secondary": "#FFA500", "accent": "#FF8C00", "glow": "#DAA520"},
    "Blood":     {"primary": "#8B0000", "secondary": "#A52A2A", "accent": "#B22222", "glow": "#DC143C"},
    "Poison":    {"primary": "#2E8B57", "secondary": "#006400", "accent": "#3CB371", "glow": "#20B2AA"},
    "Crystal":   {"primary": "#E0FFFF", "secondary": "#00CED1", "accent": "#48D1CC", "glow": "#98FB98"},
    "Plasma":    {"primary": "#FF69B4", "secondary": "#FF1493", "accent": "#DB7093", "glow": "#FF6347"},
}

# Base colors (from TRINITY card)
BASE_COLORS = {
    "bg_primary": "#0A0412",
    "bg_secondary": "#1E0A3C",
    "text_primary": "#FFFFFF",
    "text_secondary": "#CCCCCC",
    "accent_gold": "#FFD700",
    "accent_purple": "#8A2BE2",
    "accent_cyan": "#00FFFF",
}

# Fonts (fallback to default if not found)
try:
    FONT_TITLE = ImageFont.truetype(os.path.join(FONT_DIR, "arialbd.ttf"), 72)
    FONT_SUBTITLE = ImageFont.truetype(os.path.join(FONT_DIR, "arial.ttf"), 36)
    FONT_BODY = ImageFont.truetype(os.path.join(FONT_DIR, "arial.ttf"), 24)
    FONT_SMALL = ImageFont.truetype(os.path.join(FONT_DIR, "arial.ttf"), 18)
except:
    FONT_TITLE = ImageFont.load_default()
    FONT_SUBTITLE = ImageFont.load_default()
    FONT_BODY = ImageFont.load_default()
    FONT_SMALL = ImageFont.load_default()

# ======================
# HELPER FUNCTIONS
# ======================
def hex_to_rgb(hex_color: str) -> Tuple[int, int, int]:
    """Convert hex color to RGB tuple."""
    hex_color = hex_color.lstrip("#")
    return tuple(int(hex_color[i:i+2], 16) for i in (0, 2, 4))

def create_gradient(size: Tuple[int, int], color1: str, color2: str) -> Image.Image:
    """Create a vertical gradient background."""
    base = Image.new("RGB", size, hex_to_rgb(color1))
    top = Image.new("RGB", size, hex_to_rgb(color2))
    mask = Image.new("L", size)
    mask_data = np.linspace(0, 255, size[1]).astype(np.uint8)
    mask_data = np.tile(mask_data, (size[0], 1))
    mask.putdata(mask_data.flatten())
    gradient = Image.composite(base, top, mask)
    return gradient

def draw_text_with_outline(
    draw: ImageDraw.Draw,
    text: str,
    position: Tuple[int, int],
    font: ImageFont.FreeTypeFont,
    fill: str,
    outline: str = "#000000",
    outline_width: int = 2,
) -> None:
    """Draw text with a black outline (for readability)."""
    x, y = position
    for dx in range(-outline_width, outline_width + 1):
        for dy in range(-outline_width, outline_width + 1):
            if dx == 0 and dy == 0:
                continue
            draw.text((x + dx, y + dy), text, font=font, fill=outline)
    draw.text((x, y), text, font=font, fill=fill)

def wrap_text(text: str, max_width: int, font: ImageFont.FreeTypeFont) -> str:
    """Wrap text to fit within max_width pixels."""
    avg_char_width = sum(font.getsize(char)[0] for char in "abcdefghijklmnopqrstuvwxyz") / 26
    max_chars = int(max_width / avg_char_width)
    return textwrap.fill(text, width=max_chars)

def load_character_art(element: str, name: str) -> Optional[Image.Image]:
    """Load character art from assets folder."""
    art_path = os.path.join(ASSETS_DIR, "character_art", element.lower(), f"{name}.png")
    if os.path.exists(art_path):
        return Image.open(art_path).convert("RGBA")
    return None

# ======================
# CARD GENERATION
# ======================
def generate_card(row: Dict[str, str]) -> Image.Image:
    """Generate a single card from a CSV row."""
    # Extract data
    name = row.get("name", "UNKNOWN")
    tagline = row.get("tagline", "")
    element = row.get("element", "Void")
    card_id = row.get("card_id", "XXXXXX")
    construct_class = row.get("construct_class", "Omega-Ascendent NetP")
    faction = row.get("faction", "Celestial Order")
    threat_rank = int(row.get("threat_rank", 5))
    origin_matrix = json.loads(row.get("origin_matrix", "[]"))  # Expects JSON array
    profile = row.get("profile", "")
    hp = int(row.get("hp", 2000))
    atk = int(row.get("atk", 260))
    rapid = int(row.get("rapid", 180))
    charge = int(row.get("charge", 200))
    defense = int(row.get("defense", 180))
    sig_name = row.get("signature_program_name", "TRINITY GENESIS")
    sig_cost = row.get("signature_program_cost", "200")
    sig_effect = row.get("signature_program_effect", "Erases all enemy Programs from the field.")
    lore = row.get("lore_data", "")

    # Get element colors
    elem_colors = ELEMENT_COLORS.get(element, ELEMENT_COLORS["Void"])
    primary = elem_colors["primary"]
    secondary = elem_colors["secondary"]
    accent = elem_colors["accent"]
    glow = elem_colors["glow"]

    # Create card canvas
    card = Image.new("RGB", CARD_SIZE, hex_to_rgb(BASE_COLORS["bg_primary"]))
    draw = ImageDraw.Draw(card)

    # ========== BACKGROUND ==========
    # Add element-themed gradient overlay
    gradient = create_gradient(CARD_SIZE, BASE_COLORS["bg_secondary"], primary)
    card.paste(gradient, (0, 0), gradient)

    # Add subtle noise for texture
    noise = np.random.randint(0, 64, CARD_SIZE + (3,), dtype=np.uint8)
    noise_img = Image.fromarray(noise, "RGB")
    card.paste(noise_img, (0, 0), Image.new("L", CARD_SIZE, 20))

    # ========== HEADER ==========
    # Name (top-left)
    draw_text_with_outline(
        draw, name, (50, 30), FONT_TITLE, primary, "#000000", 3
    )
    # Tagline (under name)
    draw_text_with_outline(
        draw, tagline, (50, 110), FONT_SUBTITLE, BASE_COLORS["text_secondary"]
    )
    # ID (top-right)
    draw_text_with_outline(
        draw, card_id, (CARD_SIZE[0] - 200, 30), FONT_SMALL, BASE_COLORS["accent_gold"]
    )
    # Construct Class (top-right, below ID)
    draw_text_with_outline(
        draw, construct_class, (CARD_SIZE[0] - 250, 60), FONT_SMALL, BASE_COLORS["accent_cyan"]
    )

    # ========== CHARACTER ART ==========
    char_art = load_character_art(element, name)
    if char_art:
        # Resize to fit (centered, max height 600px)
        char_art.thumbnail((600, 600))
        offset = (
            (CARD_SIZE[0] - char_art.width) // 2,
            150  # Below header
        )
        # Add glow effect
        glow_layer = Image.new("RGBA", char_art.size, (*hex_to_rgb(glow), 128))
        glow_layer = glow_layer.filter(ImageFilter.GaussianBlur(20))
        card.paste(glow_layer, offset, glow_layer)
        card.paste(char_art, offset, char_art)

    # ========== ORIGIN MATRIX ==========
    draw_text_with_outline(
        draw, "ORIGIN MATRIX", (50, 700), FONT_SUBTITLE, BASE_COLORS["accent_gold"]
    )
    y_offset = 740
    for i, (src_name, src_traits) in enumerate(origin_matrix[:3]):  # Max 3 sources
        icon = "👼" if "SERAPH" in src_name else "⚔️" if "STRIFE" in src_name else "👁️"
        draw_text_with_outline(
            draw, f"{icon} {src_name}", (60, y_offset), FONT_BODY, BASE_COLORS["text_primary"]
        )
        for trait in src_traits:
            draw_text_with_outline(
                draw, f" - {trait}", (80, y_offset + 30), FONT_SMALL, BASE_COLORS["text_secondary"]
            )
            y_offset += 25

    # ========== PROFILE ==========
    draw_text_with_outline(
        draw, "PROFILE", (50, y_offset + 20), FONT_SUBTITLE, BASE_COLORS["accent_gold"]
    )
    wrapped_profile = wrap_text(profile, 500, FONT_BODY)
    draw_text_with_outline(
        draw, wrapped_profile, (50, y_offset + 50), FONT_BODY, BASE_COLORS["text_primary"]
    )

    # ========== CORE STATS ==========
    stats = [
        ("HP", hp, 2000),
        ("ATK", atk, 300),
        ("RAPID", rapid, 200),
        ("CHARGE", charge, 200),
        ("DEFENSE", defense, 200),
    ]
    draw_text_with_outline(
        draw, "CORE STATS", (50, y_offset + 150), FONT_SUBTITLE, BASE_COLORS["accent_gold"]
    )
    stat_y = y_offset + 180
    for stat_name, value, max_val in stats:
        # Stat name
        draw_text_with_outline(
            draw, stat_name, (50, stat_y), FONT_BODY, BASE_COLORS["text_primary"]
        )
        # Bar background
        bar_width = 300
        bar_height = 20
        bar_x = 150
        bar_y = stat_y - 5
        draw.rectangle(
            [(bar_x, bar_y), (bar_x + bar_width, bar_y + bar_height)],
            fill=hex_to_rgb("#333333"),
            outline=hex_to_rgb("#555555"),
        )
        # Bar fill
        bar_fill_width = int((value / max_val) * bar_width)
        draw.rectangle(
            [(bar_x, bar_y), (bar_x + bar_fill_width, bar_y + bar_height)],
            fill=hex_to_rgb(primary),
        )
        # Stat value
        draw_text_with_outline(
            draw, str(value), (bar_x + bar_width + 10, stat_y), FONT_BODY, BASE_COLORS["text_primary"]
        )
        stat_y += 30

    # ========== SIGNATURE PROGRAM ==========
    sig_y = 700
    draw_text_with_outline(
        draw, "SIGNATURE PROGRAM", (600, sig_y), FONT_SUBTITLE, BASE_COLORS["accent_gold"]
    )
    # Gold border box
    box_padding = 20
    sig_text = f"{sig_name}\nCost: {sig_cost}\n{sig_effect}"
    wrapped_sig = wrap_text(sig_text, 300, FONT_BODY)
    text_height = draw.textlength(wrapped_sig, font=FONT_BODY) / 300 * 20 * wrapped_sig.count("\n")
    draw.rectangle(
        [
            (580, sig_y + 30),
            (580 + 340, sig_y + 30 + int(text_height) + box_padding * 2)
        ],
        outline=hex_to_rgb(BASE_COLORS["accent_gold"]),
        width=3,
    )
    draw_text_with_outline(
        draw, wrapped_sig, (600, sig_y + 50), FONT_BODY, BASE_COLORS["text_primary"]
    )

    # ========== LORE DATA ==========
    lore_y = 1000
    draw_text_with_outline(
        draw, "LORE DATA", (50, lore_y), FONT_SUBTITLE, BASE_COLORS["accent_gold"]
    )
    wrapped_lore = wrap_text(lore, 1000, FONT_SMALL)
    draw_text_with_outline(
        draw, wrapped_lore, (50, lore_y + 30), FONT_SMALL, BASE_COLORS["text_secondary"]
    )

    # ========== FACTION & THREAT RANK ==========
    draw_text_with_outline(
        draw, "FACTION", (50, 1300), FONT_SUBTITLE, BASE_COLORS["accent_gold"]
    )
    draw_text_with_outline(
        draw, faction, (50, 1330), FONT_BODY, hex_to_rgb(secondary)
    )
    # Threat rank stars
    star = "★"
    draw_text_with_outline(
        draw, star * threat_rank, (50, 1360), FONT_BODY, BASE_COLORS["accent_gold"]
    )

    # ========== FOOTER ==========
    draw.line(
        [(0, CARD_SIZE[1] - 50), (CARD_SIZE[0], CARD_SIZE[1] - 50)],
        fill=hex_to_rgb(BASE_COLORS["accent_purple"]),
        width=2,
    )
    draw_text_with_outline(
        draw, f"{card_id} // DATA CARD", (50, CARD_SIZE[1] - 40), FONT_SMALL, BASE_COLORS["text_secondary"]
    )
    draw_text_with_outline(
        draw, "001 - LEGENDARY CONSTRUCT", (CARD_SIZE[0] - 300, CARD_SIZE[1] - 40), FONT_SMALL, BASE_COLORS["text_secondary"]
    )

    return card

# ======================
# MAIN EXECUTION
# ======================
def main():
    # Create output directory
    os.makedirs(OUTPUT_DIR, exist_ok=True)

    # Read CSV
    with open(CSV_PATH, mode="r", encoding="utf-8") as f:
        reader = csv.DictReader(f)
        for i, row in enumerate(reader):
            print(f"Generating card {i+1}: {row.get('name', 'UNKNOWN')}")
            card = generate_card(row)
            output_path = os.path.join(OUTPUT_DIR, f"{row.get('card_id', f'card_{i}')}.png")
            card.save(output_path)
            print(f"Saved to {output_path}")

if __name__ == "__main__":
    main()
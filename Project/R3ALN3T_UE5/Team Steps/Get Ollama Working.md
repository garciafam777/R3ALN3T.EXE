import requests
import base64

# CONFIGURE THESE (Ollama runs locally on port 11434 by default)
OLLAMA_HOST = "http://localhost:11434"
VISION_MODEL = "llava"      # From Pinokio's Llava install
CODE_MODEL = "codellama"    # From Pinokio's CodeLLama install

def analyze_game_asset(image_path):
    """Use Llava (vision) to describe a game asset/screenshot"""
    with open(image_path, "rb") as f:
        img_b64 = base64.b64encode(f.read()).decode('utf-8')
    
    payload = {
        "model": VISION_MODEL,
        "prompt": "Describe this game asset for a developer: What is it? Suggest improvements for gameplay/clarity.",
        "images": [img_b64],
        "stream": False
    }
    response = requests.post(f"{OLLAMA_HOST}/api/generate", json=payload)
    return response.json()["response"]

def generate_game_code(description):
    """Use CodeLLama to generate starter code from the vision description"""
    payload = {
        "model": CODE_MODEL,
        "prompt": f"Write Python/Pygame code for a game mechanic based on this: {description}\nKeep it simple, well-commented, and ready to run.",
        "stream": False
    }
    response = requests.post(f"{OLLAMA_HOST}/api/generate", json=payload)
    return response.json()["response"]

# 🎮 YOUR GAME DEV WORKFLOW:
# 1. Take a screenshot of your game level/asset
asset_desc = analyze_game_asset("screenshot.png")
print("👁️ Vision Analysis:", asset_desc)

# 2. Generate code based on that analysis
game_code = generate_game_code(asset_desc)
print("\n💻 Generated Code:\n", game_code)

# 3. Save code to file → test in your game engine!
with open("generated_mechanic.py", "w") as f:
    f.write(game_code)

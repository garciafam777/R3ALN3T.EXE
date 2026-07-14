"""
NETAdmin_EXE AI Backend
Orchestrator for Ollama-powered AI agents
"""

from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
import uvicorn

app = FastAPI(title="NETAdmin_EXE AI Backend")

# Configure CORS for Godot/UE5 integration.
# G8/F1 remediation (Joker): no wildcard + credentials (invalid + unsafe). Explicit allow-list,
# overridable via R3ALN3T_CORS_ORIGINS (comma-separated); localhost defaults for local dev.
import os
_ALLOWED = [o.strip() for o in os.environ.get("R3ALN3T_CORS_ORIGINS", "http://localhost:8080,http://127.0.0.1:8080").split(",") if o.strip()]
app.add_middleware(
    CORSMiddleware,
    allow_origins=_ALLOWED,
    allow_credentials=True,
    allow_methods=["GET", "POST", "PUT", "DELETE", "OPTIONS"],
    allow_headers=["*"],
)

@app.get("/")
async def root():
    return {"status": "online", "service": "NETAdmin_EXE AI Backend"}

@app.get("/health")
async def health_check():
    return {"status": "healthy"}

@app.post("/encrypt")
async def encrypt_to_net():
    # Hex -> Hash animation logic + Ollama agent coordination
    return {"status": "encrypting", "message": "Uploading to N3T..."}

@app.post("/decrypt")
async def decrypt_to_ped():
    return {"status": "decrypting", "message": "Downloading back to PED..."}

if __name__ == "__main__":
    uvicorn.run(app, host="127.0.0.1", port=8000)

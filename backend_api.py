"""
R3ALN3T Backend - REST API Endpoints
FastAPI service for UE5 frontend integration
"""

from fastapi import FastAPI, HTTPException, WebSocket, Query
from fastapi.middleware.cors import CORSMiddleware
from fastapi.responses import JSONResponse
import uvicorn
import logging
from datetime import datetime
from typing import List, Optional, Dict
import uuid

from data_models import (
    PlayerCharacter, NetPConstruct, BattleState, BattleChip, ChipFolder,
    CreatePlayerRequest, CreatePlayerResponse, StartBattleRequest, StartBattleResponse,
    ExecuteTurnRequest, ExecuteTurnResponse, SaveGameRequest, SaveGameResponse,
    APIResponse, ErrorResponse, CareerType, ElementType, FactionType, 
    CorruptionLevel, BaseStats, ElementAffinities, AlignmentType
)

# Configure logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

# Initialize FastAPI app
app = FastAPI(
    title="R3ALN3T.EXE Backend",
    description="Backend API for R3ALN3T TCG + Battle Network game",
    version="1.0.0"
)

# CORS configuration for UE5
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

# ============================================================================
# IN-MEMORY STORAGE (Replace with DB in production)
# ============================================================================

players_db: Dict[str, PlayerCharacter] = {}
battles_db: Dict[str, BattleState] = {}
netps_db: Dict[str, NetPConstruct] = {}
chips_db: Dict[str, BattleChip] = {}
folders_db: Dict[str, ChipFolder] = {}

# ============================================================================
# HEALTH & STATUS
# ============================================================================

@app.get("/health", tags=["Health"])
async def health_check():
    """Health check endpoint"""
    return APIResponse(
        success=True,
        status_code=200,
        message="R3ALN3T Backend is online",
        data={
            "players_count": len(players_db),
            "battles_count": len(battles_db),
            "timestamp": datetime.utcnow().isoformat()
        }
    )


@app.get("/", tags=["Root"])
async def root():
    """Root endpoint"""
    return {
        "service": "R3ALN3T.EXE Backend",
        "version": "1.0.0",
        "status": "online",
        "endpoints": {
            "health": "/health",
            "docs": "/docs",
            "players": "/api/v1/players",
            "battles": "/api/v1/battles"
        }
    }


# ============================================================================
# PLAYER ENDPOINTS
# ============================================================================

@app.post("/api/v1/players/create", response_model=CreatePlayerResponse, tags=["Players"])
async def create_player(request: CreatePlayerRequest):
    """Create a new player character"""
    try:
        # Generate initial NetP
        initial_netp = NetPConstruct(
            name=f"{request.element} Construct",
            tier="DELTA",
            alignment="Mechanical",
            element=request.element,
            faction_lean=FactionType.NEUTRAL,
            base_stats=BaseStats(hp=80, attack=10, defense=8, speed=9, special_attack=12, special_defense=9),
            current_hp=80,
            level=1
        )
        netps_db[initial_netp.id] = initial_netp

        # Create player
        player = PlayerCharacter(
            username=request.username,
            career=request.career,
            element=request.element,
            alignment=AlignmentType.TRUE_NEUTRAL,
            base_stats=BaseStats(hp=100, attack=8, defense=6, speed=10, special_attack=12, special_defense=8),
            element_affinities=ElementAffinities(primary=request.element),
            active_netp=initial_netp,
            netp_roster=[initial_netp],
            money=500
        )
        players_db[player.id] = player

        logger.info(f"Player created: {player.username} (ID: {player.id})")

        return CreatePlayerResponse(
            player=player,
            initial_netp=initial_netp,
            message=f"Player {request.username} created successfully!"
        )

    except Exception as e:
        logger.error(f"Error creating player: {str(e)}")
        raise HTTPException(status_code=500, detail=str(e))


@app.get("/api/v1/players/{player_id}", response_model=PlayerCharacter, tags=["Players"])
async def get_player(player_id: str):
    """Retrieve player data"""
    if player_id not in players_db:
        raise HTTPException(status_code=404, detail="Player not found")
    
    return players_db[player_id]


@app.put("/api/v1/players/{player_id}", response_model=PlayerCharacter, tags=["Players"])
async def update_player(player_id: str, player_data: PlayerCharacter):
    """Update player data"""
    if player_id not in players_db:
        raise HTTPException(status_code=404, detail="Player not found")
    
    player_data.last_save = datetime.utcnow()
    players_db[player_id] = player_data
    logger.info(f"Player updated: {player_id}")
    
    return player_data


@app.get("/api/v1/players", response_model=List[PlayerCharacter], tags=["Players"])
async def list_players(limit: int = Query(10, le=100)):
    """List all players (paginated)"""
    return list(players_db.values())[:limit]


# ============================================================================
# NETP ENDPOINTS
# ============================================================================

@app.get("/api/v1/netps/{netp_id}", response_model=NetPConstruct, tags=["NetP"])
async def get_netp(netp_id: str):
    """Retrieve NetP construct data"""
    if netp_id not in netps_db:
        raise HTTPException(status_code=404, detail="NetP not found")
    
    return netps_db[netp_id]


@app.post("/api/v1/netps/recruit", response_model=NetPConstruct, tags=["NetP"])
async def recruit_netp(
    player_id: str = Query(...),
    tier: str = Query(...),
    element: ElementType = Query(...),
    alignment: str = Query(...)
):
    """Recruit a new NetP (called during gameplay)"""
    if player_id not in players_db:
        raise HTTPException(status_code=404, detail="Player not found")
    
    new_netp = NetPConstruct(
        name=f"NetP-{tier}",
        tier=tier,
        alignment=alignment,
        element=element,
        faction_lean=FactionType.NEUTRAL,
        base_stats=BaseStats(hp=100, attack=12, defense=10, speed=10, special_attack=14, special_defense=10),
        current_hp=100,
        level=1
    )
    
    netps_db[new_netp.id] = new_netp
    player = players_db[player_id]
    player.netp_roster.append(new_netp)
    
    logger.info(f"NetP recruited: {new_netp.name} for player {player_id}")
    
    return new_netp


# ============================================================================
# CHIP & FOLDER ENDPOINTS
# ============================================================================

@app.post("/api/v1/chips/create", response_model=BattleChip, tags=["Chips"])
async def create_chip(chip: BattleChip):
    """Create a new battle chip"""
    chips_db[chip.id] = chip
    return chip


@app.get("/api/v1/chips", response_model=List[BattleChip], tags=["Chips"])
async def list_chips(
    element: Optional[ElementType] = Query(None),
    rarity: Optional[str] = Query(None)
):
    """List all available chips (with optional filters)"""
    chips = list(chips_db.values())
    
    if element:
        chips = [c for c in chips if c.element == element]
    if rarity:
        chips = [c for c in chips if c.rarity == rarity]
    
    return chips


@app.post("/api/v1/folders/create", response_model=ChipFolder, tags=["Folders"])
async def create_folder(player_id: str = Query(...), name: str = Query(...)):
    """Create a new chip folder"""
    if player_id not in players_db:
        raise HTTPException(status_code=404, detail="Player not found")
    
    folder = ChipFolder(player_id=player_id, name=name)
    folders_db[folder.id] = folder
    
    logger.info(f"Folder created: {name} for player {player_id}")
    return folder


@app.put("/api/v1/folders/{folder_id}/add-chip", response_model=ChipFolder, tags=["Folders"])
async def add_chip_to_folder(folder_id: str, chip_id: str = Query(...)):
    """Add chip to folder"""
    if folder_id not in folders_db:
        raise HTTPException(status_code=404, detail="Folder not found")
    if chip_id not in chips_db:
        raise HTTPException(status_code=404, detail="Chip not found")
    
    folder = folders_db[folder_id]
    chip = chips_db[chip_id]
    
    # Check max chips
    if len(folder.chips) >= folder.max_chips:
        raise HTTPException(status_code=400, detail="Folder is full")
    
    # Check Greek letter limit
    same_code = [c for c in folder.chips if c.code == chip.code]
    if len(same_code) >= folder.greek_letter_limit:
        raise HTTPException(status_code=400, detail=f"Maximum {folder.greek_letter_limit} chips with code '{chip.code}'")
    
    folder.chips.append(chip)
    folder.last_modified = datetime.utcnow()
    
    return folder


# ============================================================================
# BATTLE ENDPOINTS
# ============================================================================

@app.post("/api/v1/battles/start", response_model=StartBattleResponse, tags=["Battles"])
async def start_battle(
    player_id: str = Query(...),
    enemy_netp_id: str = Query(...),
    chip_folder_id: str = Query(...)
):
    """Start a new battle"""
    if player_id not in players_db:
        raise HTTPException(status_code=404, detail="Player not found")
    if enemy_netp_id not in netps_db:
        raise HTTPException(status_code=404, detail="Enemy NetP not found")
    if chip_folder_id not in folders_db:
        raise HTTPException(status_code=404, detail="Chip folder not found")
    
    player = players_db[player_id]
    enemy_netp = netps_db[enemy_netp_id]
    chip_folder = folders_db[chip_folder_id]
    
    # Create initial battle state
    from data_models import BattleGrid, BattleGridPanel, PanelState
    grid = BattleGrid(
        battle_id=str(uuid.uuid4()),
        player_panels=[[BattleGridPanel(x=x, y=y, state=PanelState.NORMAL, owner='player') for x in range(4)] for y in range(4)],
        enemy_panels=[[BattleGridPanel(x=x, y=y, state=PanelState.NORMAL, owner='enemy') for x in range(4)] for y in range(4)],
        current_turn=0,
        max_turns=50,
    )
    battle = BattleState(
        player=player,
        player_netp=player.active_netp,
        enemy_netp=enemy_netp,
        player_active_folder=chip_folder,
        player_hp=player.active_netp.current_hp,
        enemy_hp=enemy_netp.current_hp,
        grid=grid,
    )
    
    battles_db[battle.id] = battle
    logger.info(f"Battle started: {battle.id} ({player.username} vs {enemy_netp.name})")
    
    return JSONResponse(content={
        "battle_state": battle.model_dump(mode="json"),
        "message": "Battle initialized. Waiting for chip placement."
    })


@app.get("/api/v1/battles/{battle_id}", response_model=BattleState, tags=["Battles"])
async def get_battle(battle_id: str):
    """Get current battle state"""
    if battle_id not in battles_db:
        raise HTTPException(status_code=404, detail="Battle not found")
    
    return battles_db[battle_id]


@app.post("/api/v1/battles/{battle_id}/execute-turn", response_model=ExecuteTurnResponse, tags=["Battles"])
async def execute_turn(battle_id: str, request: ExecuteTurnRequest):
    """Execute a battle turn (player places chips)"""
    if battle_id not in battles_db:
        raise HTTPException(status_code=404, detail="Battle not found")
    
    battle = battles_db[battle_id]
    phase_log = []
    
    try:
        # Validate chip placements
        for placement in request.chip_placements:
            chip_id = placement.get("chip_id")
            if chip_id not in chips_db:
                phase_log.append(f"ERROR: Chip {chip_id} not found")
                continue
            
            # Place chip on grid
            x, y = placement.get("x"), placement.get("y")
            phase_log.append(f"Placed chip {chips_db[chip_id].name} at ({x}, {y})")
        
        # AI chooses moves
        phase_log.append("Enemy NetP executing turn...")
        
        # Simulate battle resolution
        phase_log.append("Battle phase: RESOLUTION")
        battle.turn += 1
        battle.phase = "execution"
        battle.last_updated = datetime.utcnow()
        
        # Simple health simulation
        import random
        player_damage = random.randint(5, 20)
        enemy_damage = random.randint(5, 20)
        
        battle.player_hp = max(0, battle.player_hp - enemy_damage)
        battle.enemy_hp = max(0, battle.enemy_hp - player_damage)
        
        phase_log.append(f"Player took {enemy_damage} damage")
        phase_log.append(f"Enemy took {player_damage} damage")
        
        # Check for battle end
        if battle.player_hp <= 0:
            battle.victory = False
            battle.phase = "end"
            phase_log.append("DEFEAT!")
        elif battle.enemy_hp <= 0:
            battle.victory = True
            battle.phase = "end"
            battle.experience_gained = 100
            battle.money_gained = 250
            phase_log.append("VICTORY!")
        
        battles_db[battle_id] = battle
        logger.info(f"Battle turn executed: {battle_id} (Turn {battle.turn})")
        
        return ExecuteTurnResponse(
            battle_state=battle,
            phase_log=phase_log,
            message="Turn executed successfully"
        )
    
    except Exception as e:
        logger.error(f"Error executing turn: {str(e)}")
        raise HTTPException(status_code=500, detail=str(e))


@app.post("/api/v1/battles/{battle_id}/end", tags=["Battles"])
async def end_battle(battle_id: str):
    """End the battle and apply rewards"""
    if battle_id not in battles_db:
        raise HTTPException(status_code=404, detail="Battle not found")
    
    battle = battles_db[battle_id]
    player = battle.player
    
    # Apply rewards
    if battle.victory:
        player.experience += battle.experience_gained
        player.money += battle.money_gained
        logger.info(f"Battle rewards applied: {battle_id}")
    
    # Update player
    players_db[player.id] = player
    
    return APIResponse(
        success=True,
        status_code=200,
        message="Battle ended",
        data={
            "victory": battle.victory,
            "experience": battle.experience_gained,
            "money": battle.money_gained
        }
    )


# ============================================================================
# SAVE/LOAD ENDPOINTS
# ============================================================================

@app.post("/api/v1/save", response_model=SaveGameResponse, tags=["Save/Load"])
async def save_game(request: SaveGameRequest):
    """Save game state"""
    try:
        # Update player
        players_db[request.player_id] = request.player_state
        
        # Save active battle if exists
        if request.active_battle:
            battles_db[request.active_battle.id] = request.active_battle
        
        save_id = f"save_{request.player_id}_{datetime.utcnow().timestamp()}"
        logger.info(f"Game saved: {save_id}")
        
        return SaveGameResponse(
            save_id=save_id,
            timestamp=datetime.utcnow(),
            message="Game saved successfully"
        )
    
    except Exception as e:
        logger.error(f"Error saving game: {str(e)}")
        raise HTTPException(status_code=500, detail=str(e))


@app.get("/api/v1/load/{player_id}", response_model=PlayerCharacter, tags=["Save/Load"])
async def load_game(player_id: str):
    """Load saved game"""
    if player_id not in players_db:
        raise HTTPException(status_code=404, detail="Save file not found")
    
    return players_db[player_id]


# ============================================================================
# WEBSOCKET FOR REAL-TIME BATTLE SYNC
# ============================================================================

@app.websocket("/ws/battle/{battle_id}")
async def websocket_battle(websocket: WebSocket, battle_id: str):
    """WebSocket for real-time battle state sync"""
    await websocket.accept()
    logger.info(f"WebSocket connected for battle {battle_id}")
    
    try:
        while True:
            # Receive commands from UE5
            data = await websocket.receive_json()
            
            if data.get("action") == "get_state":
                if battle_id in battles_db:
                    await websocket.send_json({
                        "type": "battle_state",
                        "data": battles_db[battle_id].dict()
                    })
            
            elif data.get("action") == "update_state":
                if battle_id in battles_db:
                    battles_db[battle_id].last_updated = datetime.utcnow()
                    await websocket.send_json({
                        "type": "ack",
                        "message": "State updated"
                    })
    
    except Exception as e:
        logger.error(f"WebSocket error: {str(e)}")
    finally:
        logger.info(f"WebSocket disconnected for battle {battle_id}")


# ============================================================================
# ERROR HANDLERS
# ============================================================================

@app.exception_handler(HTTPException)
async def http_exception_handler(request, exc):
    return JSONResponse(
        status_code=exc.status_code,
        content={
            "status_code": exc.status_code,
            "error": exc.detail,
            "details": str(exc)
        }
    )


@app.exception_handler(Exception)
async def general_exception_handler(request, exc):
    logger.error(f"Unhandled exception: {str(exc)}")
    return JSONResponse(
        status_code=500,
        content={
            "status_code": 500,
            "error": "Internal server error",
            "details": str(exc)
        }
    )


# ============================================================================
# STARTUP & SHUTDOWN
# ============================================================================

@app.on_event("startup")
async def startup_event():
    """Initialize on startup"""
    logger.info("R3ALN3T Backend starting up...")
    
    # Initialize some test chips
    test_chips = [
        BattleChip(
            name="Vulcan",
            code="A",
            chip_type="Attack",
            element=ElementType.FIRE,
            rarity="Common",
            power=40,
            accuracy=0.95,
            effect_description="Fire blast dealing 40 damage"
        ),
        BattleChip(
            name="Aqua Needle",
            code="B",
            chip_type="Attack",
            element=ElementType.AQUA,
            rarity="Common",
            power=50,
            accuracy=0.90,
            effect_description="Water attack dealing 50 damage"
        ),
    ]
    
    for chip in test_chips:
        chips_db[chip.id] = chip
    
    logger.info(f"Initialized {len(test_chips)} test chips")


@app.on_event("shutdown")
async def shutdown_event():
    """Cleanup on shutdown"""
    logger.info("R3ALN3T Backend shutting down...")
    logger.info(f"Final state: {len(players_db)} players, {len(battles_db)} battles")


# ============================================================================
# MAIN
# ============================================================================

if __name__ == "__main__":
    uvicorn.run(
        app,
        host="0.0.0.0",
        port=8000,
        log_level="info"
    )

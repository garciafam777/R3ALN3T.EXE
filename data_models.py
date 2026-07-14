"""
R3ALN3T Backend - Shared Data Models
Frontend-Backend alignment layer for UE5 + Python FastAPI integration
"""

from pydantic import BaseModel, Field
from typing import List, Optional, Dict, Any
from enum import Enum
import uuid
from datetime import datetime


# ============================================================================
# ENUMERATIONS
# ============================================================================

class ElementType(str, Enum):
    """6 Element system for NetP and progression"""
    FIRE = "Fire"
    WATER = "Water"
    LIGHTNING = "Lightning"
    ICE = "Ice"
    WIND = "Wind"
    EARTH = "Earth"


class CareerType(str, Enum):
    """6 Career paths with alignment lean"""
    NETOP = "NetOp"  # Hacker
    SCIENTIST = "Scientist"  # Academic
    SOLDIER = "Soldier"  # Military
    JACKER = "Jacker"  # Criminal
    EXECUTIVE = "Executive"  # Corporate
    WANDERER = "Wanderer"  # Explorer


class FactionType(str, Enum):
    """6 Dynamic factions determining ending"""
    GOVERNMENT = "Government"
    CORPORATE = "Corporate"
    UNDERGROUND = "Underground"
    NATURE = "Nature"
    NEUTRAL = "Neutral"
    CHAOS = "Chaos"


class AlignmentType(str, Enum):
    """Character alignment spectrum"""
    CHAOTIC_EVIL = "Chaotic Evil"
    CHAOTIC_NEUTRAL = "Chaotic Neutral"
    CHAOTIC_GOOD = "Chaotic Good"
    NEUTRAL_EVIL = "Neutral Evil"
    TRUE_NEUTRAL = "True Neutral"
    NEUTRAL_GOOD = "Neutral Good"
    LAWFUL_EVIL = "Lawful Evil"
    LAWFUL_NEUTRAL = "Lawful Neutral"
    LAWFUL_GOOD = "Lawful Good"


class ChipRarity(str, Enum):
    """Chip rarity tiers"""
    COMMON = "Common"
    UNCOMMON = "Uncommon"
    RARE = "Rare"
    EPIC = "Epic"
    LEGENDARY = "Legendary"
    MYTHIC = "Mythic"


class PanelState(str, Enum):
    """Battle grid panel states"""
    NORMAL = "Normal"
    CRACKED = "Cracked"
    HIDDEN = "Hidden"
    BROKEN = "Broken"
    BLESSED = "Blessed"
    CURSED = "Cursed"


class CorruptionLevel(str, Enum):
    """Player corruption tracking (affects story branching)"""
    PURE = "Pure"
    TAINTED = "Tainted"
    CORRUPTED = "Corrupted"
    COMPROMISED = "Compromised"
    INFECTED = "Infected"


# ============================================================================
# STAT & ATTRIBUTE MODELS
# ============================================================================

class BaseStats(BaseModel):
    """Core combat statistics (mirrored in UE5)"""
    hp: int = Field(100, description="Hit Points")
    attack: int = Field(10, description="Physical Attack")
    defense: int = Field(5, description="Physical Defense")
    speed: int = Field(8, description="Action speed/priority")
    special_attack: int = Field(10, description="Special Attack/Chip Damage")
    special_defense: int = Field(5, description="Special Defense/Resistance")

    class Config:
        frozen = True  # Immutable - create new instances instead


class DerivedStats(BaseModel):
    """Calculated stats from base stats"""
    crit_rate: float = Field(0.05, description="Critical hit chance (0.0-1.0)")
    crit_damage: float = Field(1.5, description="Critical damage multiplier")
    dodge_rate: float = Field(0.0, description="Dodge chance (0.0-1.0)")
    block_rate: float = Field(0.0, description="Block chance (0.0-1.0)")
    accuracy: float = Field(0.95, description="Hit accuracy (0.0-1.0)")


class ElementResistance(BaseModel):
    """Resistance/weakness to elements"""
    element: ElementType
    resistance: float = Field(0.0, description="Resistance (-1.0 weak to 1.0 strong)")


class ElementAffinities(BaseModel):
    """Character element affinities"""
    affinities: Dict[ElementType, float] = Field(
        default_factory=lambda: {e: 0.0 for e in ElementType}
    )
    primary: ElementType = ElementType.FIRE
    secondary: Optional[ElementType] = None


# ============================================================================
# CHARACTER & PLAYER MODELS
# ============================================================================

class NetPConstruct(BaseModel):
    """NetP (Network Persona) - AI companion"""
    id: str = Field(default_factory=lambda: str(uuid.uuid4()))
    name: str
    tier: str = Field(description="OMEGA, ALPHA, BETA, etc. (16-tier hierarchy)")
    alignment: str = Field(description="Mechanical, Viral, Angelic, Demonic")
    element: ElementType
    faction_lean: str = Field(description="Government / Corporate / Underground / Nature / Neutral / Chaos")
    base_stats: BaseStats
    derived_stats: Optional[DerivedStats] = None

    # Combat state
    current_hp: int
    status_effects: List[str] = Field(default_factory=list)

    # Progression
    experience: int = 0
    level: int = 1
    created_at: datetime = Field(default_factory=datetime.utcnow)

    class Config:
        json_schema_extra = {
            "example": {
                "id": "netp-001",
                "name": "XenDros",
                "tier": "ALPHA",
                "alignment": "Mechanical",
                "element": "Lightning",
                "faction_lean": "Corporate",
                "base_stats": {"hp": 150, "attack": 15, "defense": 10, "speed": 12, "special_attack": 18, "special_defense": 12},
                "current_hp": 150,
                "level": 5,
            }
        }


class PlayerCharacter(BaseModel):
    """Player character (the NetOp/human)"""
    id: str = Field(default_factory=lambda: str(uuid.uuid4()))
    username: str
    career: CareerType
    element: ElementType
    alignment: AlignmentType
    
    # Stats
    base_stats: BaseStats
    derived_stats: Optional[DerivedStats] = None
    element_affinities: ElementAffinities
    
    # Progression & Game State
    level: int = 1
    experience: int = 0
    health: int = 100
    
    # Corruption & Alignment
    corruption_level: CorruptionLevel = CorruptionLevel.PURE
    corruption_points: int = 0
    faction_alignment: Dict[FactionType, float] = Field(
        default_factory=lambda: {f: 0.0 for f in FactionType}
    )
    
    # Resources
    money: int = 0
    battle_chips_count: int = 0
    chip_folder_count: int = 1
    
    # Progression Milestones
    day: int = 1
    rooms_cleared: int = 0
    bosses_defeated: int = 0
    
    # NetP Companion
    active_netp: Optional[NetPConstruct] = None
    netp_roster: List[NetPConstruct] = Field(default_factory=list)
    
    created_at: datetime = Field(default_factory=datetime.utcnow)
    last_save: datetime = Field(default_factory=datetime.utcnow)

    class Config:
        json_schema_extra = {
            "example": {
                "id": "player-001",
                "username": "JackHacker",
                "career": "NetOp",
                "element": "Lightning",
                "alignment": "Chaotic Good",
                "base_stats": {"hp": 100, "attack": 8, "defense": 6, "speed": 10, "special_attack": 12, "special_defense": 8},
                "level": 1,
                "corruption_level": "Pure",
                "faction_alignment": {"Government": 0.0, "Corporate": -0.5, "Underground": 0.3},
            }
        }


# ============================================================================
# BATTLE & CHIP MODELS
# ============================================================================

class BattleChip(BaseModel):
    """Individual battle chip (like Mega Man BN chips)"""
    id: str = Field(default_factory=lambda: str(uuid.uuid4()))
    name: str
    code: str = Field(description="A-Z code, used in Greek-letter grouping")
    chip_type: str = Field(description="Attack, Defense, Utility, etc.")
    element: ElementType
    rarity: ChipRarity
    power: int = Field(description="Base damage/effect power")
    accuracy: float = Field(1.0, description="Hit rate (0.0-1.0)")
    cooldown: int = Field(0, description="Turns until reusable")
    effect_description: str
    created_at: datetime = Field(default_factory=datetime.utcnow)

    class Config:
        json_schema_extra = {
            "example": {
                "id": "chip-001",
                "name": "Vulcan",
                "code": "A",
                "chip_type": "Attack",
                "element": "Fire",
                "rarity": "Common",
                "power": 40,
                "accuracy": 0.95,
                "effect_description": "Fire blast dealing 40 damage",
            }
        }


class ChipFolder(BaseModel):
    """Chip folder (like deck in TCG)"""
    id: str = Field(default_factory=lambda: str(uuid.uuid4()))
    player_id: str
    name: str
    chips: List[BattleChip] = Field(default_factory=list, max_items=30)
    
    # Folder rules
    max_chips: int = 30
    greek_letter_limit: int = 3  # Max 3 chips with same code letter
    
    created_at: datetime = Field(default_factory=datetime.utcnow)
    last_modified: datetime = Field(default_factory=datetime.utcnow)

    @property
    def total_power(self) -> int:
        """Calculate folder's total power"""
        return sum(chip.power for chip in self.chips)

    class Config:
        json_schema_extra = {
            "example": {
                "id": "folder-001",
                "player_id": "player-001",
                "name": "Lightning Blitz",
                "chips": [],  # Would be filled with BattleChips
            }
        }


class BattleGridPanel(BaseModel):
    """Individual panel on battle grid"""
    x: int = Field(description="Column (0-3 for each side)")
    y: int = Field(description="Row (0-3)")
    state: PanelState = PanelState.NORMAL
    owner: str = Field(description="'player' or 'enemy'")
    element: Optional[ElementType] = None
    chip_id: Optional[str] = None
    damage_on_step: int = 0
    turns_remaining: int = 0

    class Config:
        json_schema_extra = {
            "example": {
                "x": 0, "y": 0, "state": "Normal", "owner": "player",
                "element": "Fire", "chip_id": "chip-001", "damage_on_step": 0
            }
        }


class BattleGrid(BaseModel):
    """8×4 battle grid (4×4 player + 4×4 enemy)"""
    battle_id: str = Field(default_factory=lambda: str(uuid.uuid4()))
    player_panels: List[List[BattleGridPanel]] = Field(default_factory=lambda: _empty_grid)
    enemy_panels: List[List[BattleGridPanel]] = Field(default_factory=lambda: _empty_grid)
    current_turn: int = 0
    max_turns: int = 50

def _make_panel(owner: str, x: int, y: int) -> BattleGridPanel:
    return BattleGridPanel(x=x, y=y, state=PanelState.NORMAL, owner=owner)

def _empty_grid() -> List[List[BattleGridPanel]]:
    return [[_make_panel('player', x, y) for x in range(4)] for y in range(4)]

class BattleState(BaseModel):
    """Active battle state - synced between frontend & backend"""
    id: str = Field(default_factory=lambda: str(uuid.uuid4()))
    
    # Participants
    player: PlayerCharacter
    player_netp: NetPConstruct
    enemy_netp: NetPConstruct
    player_active_folder: Optional[ChipFolder] = None
    
    # Battle progression
    turn: int = 0
    phase: str = "planning"
    round_number: int = 1
    
    # Grid & chips
    grid: BattleGrid = Field(default_factory=BattleGrid)
    
    # Status
    player_hp: int = 0
    enemy_hp: int = 0
    player_status_effects: List[str] = Field(default_factory=list)
    enemy_status_effects: List[str] = Field(default_factory=list)
    
    # Rewards (populated at end)
    victory: bool = False
    experience_gained: int = 0
    money_gained: int = 0
    
    created_at: datetime = Field(default_factory=datetime.utcnow)
    last_updated: datetime = Field(default_factory=datetime.utcnow)

    class Config:
        json_schema_extra = {
            "example": {
                "id": "battle-001",
                "turn": 3,
                "phase": "planning",
                "round_number": 1,
                "player_hp": 95,
                "enemy_hp": 100,
                "victory": False,
            }
        }


# ============================================================================
# API REQUEST/RESPONSE MODELS
# ============================================================================

class CreatePlayerRequest(BaseModel):
    """Request body for creating new player"""
    username: str
    career: CareerType
    element: ElementType


class CreatePlayerResponse(BaseModel):
    """Response after player creation"""
    player: PlayerCharacter
    initial_netp: NetPConstruct
    message: str


class StartBattleRequest(BaseModel):
    """Request to start a new battle"""
    player_id: str
    enemy_netp_id: str
    chip_folder_id: str


class StartBattleResponse(BaseModel):
    """Response with initial battle state"""
    battle_state: BattleState
    message: str


class ExecuteTurnRequest(BaseModel):
    """Player executes turn (places chips on grid)"""
    chip_placements: List[Dict[str, Any]] = Field(
        description="List of {chip_id, x, y} placements"
    )


class ExecuteTurnResponse(BaseModel):
    """Result of turn execution"""
    battle_state: BattleState
    phase_log: List[str] = Field(description="Play-by-play events")
    message: str


class SaveGameRequest(BaseModel):
    """Request to save game state"""
    player_id: str
    player_state: PlayerCharacter
    active_battle: Optional[BattleState] = None


class SaveGameResponse(BaseModel):
    """Confirmation of save"""
    save_id: str
    timestamp: datetime
    message: str


# ============================================================================
# HELPER MODELS
# ============================================================================

class APIResponse(BaseModel):
    """Standard API response wrapper"""
    success: bool
    status_code: int
    message: str
    data: Optional[Dict[str, Any]] = None
    timestamp: datetime = Field(default_factory=datetime.utcnow)

    class Config:
        json_schema_extra = {
            "example": {
                "success": True,
                "status_code": 200,
                "message": "Operation successful",
                "data": {},
                "timestamp": "2025-01-15T10:30:00Z"
            }
        }


class ErrorResponse(BaseModel):
    """Standard error response"""
    success: bool = False
    status_code: int
    error: str
    details: Optional[str] = None
    timestamp: datetime = Field(default_factory=datetime.utcnow)

-- NETAdmin.EXE Core Database Schema
-- R34L / N3T Dual Layer + Governance System

CREATE TABLE players (
    player_id TEXT PRIMARY KEY,
    username TEXT UNIQUE,
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    last_login DATETIME,
    heat_tier INTEGER DEFAULT 0,
    man_balance INTEGER DEFAULT 0,
    corruption_level INTEGER DEFAULT 0,
    admin_level INTEGER DEFAULT 1,  -- 1=normal, 4=MCADMIN
    current_location TEXT DEFAULT 'r34l_room'
);

CREATE TABLE navis (
    navi_id TEXT PRIMARY KEY,
    owner_id TEXT REFERENCES players(player_id),
    name TEXT,
    role TEXT,                    -- SystemAdmin, Security, Coder, etc.
    base_style TEXT,
    current_style TEXT,
    level INTEGER DEFAULT 1,
    hp_max INTEGER DEFAULT 1000,
    customizer_grid_size INTEGER DEFAULT 4,  -- 4x4 → 8x8
    personality_seed TEXT,        -- For consistent dialogue style
    fatigue INTEGER DEFAULT 0,
    last_active DATETIME
);

CREATE TABLE man_transactions (
    tx_id TEXT PRIMARY KEY,
    player_id TEXT REFERENCES players(player_id),
    amount INTEGER,
    tx_type TEXT,                 -- earn_virus, spend_chip, background_script, etc.
    description TEXT,
    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
    helix_gold REAL DEFAULT 1.0,  -- Visual strand balance
    helix_blue REAL DEFAULT 1.0,
    helix_red REAL DEFAULT 1.0
);

CREATE TABLE rooms (
    room_id TEXT PRIMARY KEY,
    player_id TEXT REFERENCES players(player_id),
    layer TEXT CHECK(layer IN ('r34l', 'n3t')),  -- Physical vs Jacked-in
    last_visited DATETIME,
    cleanliness_score REAL DEFAULT 100.0,
    customization_data JSON      -- Wall art, carpet, furniture nodes
);

CREATE TABLE customizer_layouts (
    layout_id TEXT PRIMARY KEY,
    navi_id TEXT REFERENCES navis(navi_id),
    grid_size INTEGER,
    blocks JSON,                 -- Array of block placements with coordinates
    bug_heat REAL DEFAULT 0.0,
    active_glitches JSON,
    last_compiled DATETIME
);

CREATE TABLE career_progress (
    player_id TEXT REFERENCES players(player_id),
    field TEXT,                  -- SystemGovernance, Security, etc.
    tier INTEGER DEFAULT 1,
    reputation INTEGER DEFAULT 0,
    PRIMARY KEY (player_id, field)
);

CREATE TABLE active_tasks (
    task_id TEXT PRIMARY KEY,
    player_id TEXT REFERENCES players(player_id),
    navi_id TEXT REFERENCES navis(navi_id),
    task_type TEXT,
    description TEXT,
    status TEXT DEFAULT 'running',   -- running, completed, failed
    started_at DATETIME,
    completed_at DATETIME,
    reward_man INTEGER
);

-- Indexes for performance
CREATE INDEX idx_navis_owner ON navis(owner_id);
CREATE INDEX idx_transactions_player ON man_transactions(player_id);
CREATE INDEX idx_heat ON players(heat_tier);

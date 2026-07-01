-- R3ALN3T.EXE Telemetry Schema
CREATE TABLE IF NOT EXISTS position_log (
    id BIGSERIAL PRIMARY KEY,
    entity_id VARCHAR(64) NOT NULL,
    x DOUBLE PRECISION NOT NULL,
    y DOUBLE PRECISION NOT NULL,
    z DOUBLE PRECISION NOT NULL,
    layer INTEGER NOT NULL DEFAULT 0,
    timestamp_sec DOUBLE PRECISION NOT NULL,
    recorded_at TIMESTAMPTZ NOT NULL DEFAULT NOW()
);

CREATE INDEX IF NOT EXISTS idx_position_entity ON position_log(entity_id);
CREATE INDEX IF NOT EXISTS idx_position_recorded ON position_log(recorded_at);

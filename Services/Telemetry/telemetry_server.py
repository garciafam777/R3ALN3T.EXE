"""
R3ALN3T.EXE Telemetry Loopback Server
Listens on 127.0.0.1:8080 for position payloads from UE5.
Stores in Redis if available, otherwise logs to file.
"""
import json
import os
import logging
from http.server import HTTPServer, BaseHTTPRequestHandler
from datetime import datetime

LOG_DIR = os.path.join(os.path.dirname(__file__), "..", "telemetry_logs")
os.makedirs(LOG_DIR, exist_ok=True)

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger("TelemetryServer")

class PositionHandler(BaseHTTPRequestHandler):
    def do_POST(self):
        content_length = int(self.headers.get('Content-Length', 0))
        body = self.rfile.read(content_length)
        try:
            payload = json.loads(body)
            entity_id = payload.get("entity_id", "unknown")
            ts = payload.get("timestamp", 0)
            logger.info(f"POSITION {entity_id} @ ({payload.get('x'):.1f}, {payload.get('y'):.1f}, {payload.get('z'):.1f}) layer={payload.get('layer')} t={ts:.2f}")

            # Append to log file per entity
            log_path = os.path.join(LOG_DIR, f"{entity_id}.jsonl")
            with open(log_path, "a") as f:
                f.write(json.dumps({"ts": ts, "payload": payload}) + "\n")

            self.send_response(200)
            self.send_header("Content-Type", "application/json")
            self.end_headers()
            self.wfile.write(json.dumps({"status": "ok"}).encode())
        except Exception as e:
            logger.error(f"Parse error: {e}")
            self.send_response(400)
            self.end_headers()

    def do_GET(self):
        self.send_response(200)
        self.send_header("Content-Type", "application/json")
        self.end_headers()
        self.wfile.write(json.dumps({"service": "R3ALN3T Telemetry", "status": "online"}).encode())

    def log_message(self, format, *args):
        pass  # Suppress default HTTP server logs

if __name__ == "__main__":
    port = 8080
    server = HTTPServer(("127.0.0.1", port), PositionHandler)
    logger.info(f"Telemetry server listening on http://127.0.0.1:{port}")
    try:
        server.serve_forever()
    except KeyboardInterrupt:
        server.shutdown()
        logger.info("Server stopped.")

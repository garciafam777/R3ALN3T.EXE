"""
Recursive data sync for R3ALN3T backend/UE5 client alignment.
Reads UE5 Source and Content conventions and reports pointers in JSON.
"""
from pathlib import Path
import json, re
PROJECT = Path(r'C:\Users\richa\Desktop\R3ALN3T_UE5')
report = {
 'ue5_sources': [],
 'backend_models': [],
 'api_contract': [],
 'notes': [],
}

for p in (PROJECT/'Source').rglob('*.h'):
    report['ue5_sources'].append({'path': str(p.relative_to(PROJECT)), 'name': p.name})
for p in (PROJECT/'Source').rglob('*.cpp'):
    report['ue5_sources'].append({'path': str(p.relative_to(PROJECT)), 'name': p.name})
for p in [PROJECT/'data_models.py', PROJECT/'backend_api.py']:
    if p.exists():
        report['backend_models'].append(str(p.relative_to(PROJECT)))

report['api_contract'] = [
 'POST /api/v1/players/create -> CreatePlayer',
 'GET /api/v1/players/{player_id} -> GetPlayer',
 'PUT /api/v1/players/{player_id} -> UpdatePlayer',
 'GET /api/v1/netps/recruit -> RecruitNetP',
 'POST /api/v1/battles/start -> StartBattle',
 'GET /api/v1/battles/{battle_id} -> GetBattle',
 'POST /api/v1/battles/{battle_id}/execute-turn -> ExecuteTurn',
 'POST /api/v1/battles/{battle_id}/end -> EndBattle',
 'POST /api/v1/folders/create -> CreateFolder',
 'PUT /api/v1/folders/{folder_id}/add-chip -> AddChipToFolder',
 'POST /api/v1/save -> SaveGame',
 'GET /api/v1/load/{player_id} -> LoadGame',
 'WS /ws/battle/{battle_id} -> BattleSync',
]

print(json.dumps(report, indent=2))

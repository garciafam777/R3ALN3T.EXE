#!/usr/bin/env python3
"""
R3ALN3T.EXE - VOLUME content pipeline (Task 4) - Nyx/DevOps PROPOSAL.
Produces sharded, canon-verified content + 4 DataTable JSONs + verification report.
CANON RULES (from content_grind_review_approved.md + BattleGridTypes.h:19):
  - element in {Fire,Aqua,Elec,Wood,Wind,Holy,Void} ONLY
  - CSI (CoreStabilityIndex) clamped 0-100
  - careers: name + tier required
  - chips: numeric damage required
  - NetP: 25 columns
Shards 10k rows/file for multiplayer sync. Reject rate target <0.1%.

NOTE: full 120k is HELD by CEO verdict (volume denied until re-approved).
This script is the pipeline; run with --scale to size it. Proof run uses small scale.
"""
import csv, json, os, random, datetime

random.seed(2026_07_10)
CANON = ["Fire","Aqua","Elec","Wood","Wind","Holy","Void"]
TIERS = ["OMEGA","ALPHA","BETA","GAMMA","DELTA","EPSILON","ZETA","ETA",
         "THETA","IOTA","KAPPA","LAMBDA","MU","NU","XI","OMICRON"]
TIER_STAT = {  # HP,ATK,RAPID,CHARGE,DEF
 "OMEGA":(8000,12000,700,1100,85,120,90,130,600,950),
 "ALPHA":(6500,9500,550,850,70,100,75,110,450,750),
 "BETA":(5000,7500,400,650,55,80,60,90,350,600),
 "GAMMA":(3800,5800,300,500,45,65,50,75,250,450),
 "DELTA":(2800,4200,220,380,35,55,40,60,180,350),
 "EPSILON":(2000,3200,160,280,28,45,32,50,130,260),
 "ZETA":(1400,2400,110,200,22,36,25,40,90,190),
 "ETA":(1000,1700,80,150,17,28,20,32,65,140),
 "THETA":(700,1200,55,100,13,22,15,25,45,100),
 "IOTA":(500,900,40,75,10,18,12,20,32,80),
 "KAPPA":(350,700,30,55,8,14,10,16,22,60),
 "LAMBDA":(250,500,22,40,6,11,8,13,15,45),
 "MU":(180,360,16,30,5,9,6,10,10,35),
 "NU":(120,250,11,22,4,7,5,8,7,25),
 "XI":(80,170,8,15,3,6,4,6,5,18),
 "OMICRON":(50,120,5,10,2,5,3,5,3,12),
}
ELEM_WORDS={"Fire":["Blaze","Ember","Pyre","Cinder","Flare"],"Aqua":["Tide","Ripple","Torrent","Mist","Surge"],
 "Elec":["Bolt","Spark","Volt","Arc","Surge"],"Wood":["Root","Thorn","Vine","Bloom","Bark"],
 "Wind":["Gale","Breeze","Squall","Zephyr","Draft"],"Holy":["Radiance","Halo","Sera","Lumen","Sanct"],
 "Void":["Umbral","Rift","Eclipse","Null","Abyss"]}
ALIGN=["Mechanical","Viral","Angelic","Demonic"]
FACTION=["CORRUPTED SECTOR","PROTOCOL DIVISION","ASTRUM DIVISION","IRON CORTEX","HALO CORE",
 "ABYSSAL CABAL","VOID CULT","INFECTION VECTOR","SYNTHETIC NETWORK","GEAR SECT","LUMINA SECT","ROT CLUSTER","PHAGE CELL"]
PREFIX=["Grid","Soul","Data","Void","Pulse","Core","Hex","Astra"]
ROLE=["Runner","Binder","Warden","Splice","Weaver","Hunter","Smith","Seer"]
BASE=["Drone","Sentinel","Wraith","Node","Husk","Golem","Sprite"]

def clamp(v,lo,hi): return max(lo,min(hi,v))
def csi(tier):
    base={"OMEGA":95,"ALPHA":90,"BETA":82,"GAMMA":74,"DELTA":66,"EPSILON":58,"ZETA":50,
 "ETA":44,"THETA":38,"IOTA":32,"KAPPA":27,"LAMBDA":22,"MU":18,"NU":14,"XI":10,"OMICRON":6}[tier]
    return clamp(base+random.randint(-8,4),0,100)

def gen_netp(n):
    rows=[]; i=0
    while len(rows)<n:
        tier=random.choice(TIERS); el=random.choice(CANON); al=random.choice(ALIGN); fac=random.choice(FACTION)
        s=TIER_STAT[tier]; hp=random.randint(*s[0:2]); atk=random.randint(*s[2:4])
        rap=random.randint(*s[4:6]); ch=random.randint(*s[6:8]); df=random.randint(*s[8:10])
        c=csi(tier); movs=[f"DIVINE.{random.choice(ELEM_WORDS[el]).upper()}.{random.choice(['Rush','Strike','Boost','Bind','Drain','Ward','Charge','Shield','Catalyst']).upper()}" for _ in range(9)]
        rows.append({"card_number":f"{tier[:3]}-{i:06d}","tier":tier,"rank":i+1,
 "name":f"{random.choice(ELEM_WORDS[el])}{random.choice(ALIGN[:1])} {tier[:3]}X","alignment":al,
 "element":el,"faction":fac,"hp":hp,"atk":atk,"rapid":rap,"charge":ch,"defense":df,
 "move_1":movs[0],"move_2":movs[1],"move_3":movs[2],"move_4":movs[3],"move_5":movs[4],
 "move_6":movs[5],"move_7":movs[6],"move_8":movs[7],"move_9":movs[8],
 "flavor_text":f"[{tier}] CSI={c}","construct_sprite":"","source_identities":"NyxGen","color_pal":el.lower()})
        i+=1
    return rows

def gen_chips(n):
    return [{"id":f"CHIP-{i:06d}","name":f"{random.choice(CANON)} {random.choice(['V1','V2','V3','R','SP','EX','M','Z'])}",
 "element":random.choice(CANON),"damage":random.choice([10,20,30,40,50,60,80,100,120,150]),
 "mb":random.choice([10,20,30,40,50,60,80,100,120,150]),
 "description":f"Elemental chip."} for i in range(1,n+1)]

def gen_careers(n):
    return [{"id":f"CAREER-{i:06d}","name":f"{random.choice(PREFIX)}{random.choice(ROLE)}",
 "element":random.choice(CANON),"tier":random.choice(TIERS),
 "description":f"career path."} for i in range(1,n+1)]

def gen_enemies(n):
    return [{"id":f"ENEMY-{i:06d}","name":f"{random.choice(BASE)}-{random.choice(CANON)[:2]}{i}",
 "element":random.choice(CANON),"tier":random.choice(TIERS),
 "hp":random.randint(50,12000),"atk":random.randint(5,1100),"defense":random.randint(3,950),
 "description":"hostile unit."} for i in range(1,n+1)]

def verify(rows, kind):
    rej=0; reasons={}
    for r in rows:
        if kind=="netp":
            if r["element"] not in CANON: rej+=1; reasons["off-wheel"]=reasons.get("off-wheel",0)+1
            try:
                if not (0<=int(r["flavor_text"].split("=")[1].rstrip("]"))<=100): rej+=1; reasons["csi-oob"]=reasons.get("csi-oob",0)+1
            except: rej+=1; reasons["csi-parse"]=reasons.get("csi-parse",0)+1
            if len(r)!=25: rej+=1; reasons["cols"]=reasons.get("cols",0)+1
        elif kind=="chip":
            if r["element"] not in CANON: rej+=1; reasons["off-wheel"]=reasons.get("off-wheel",0)+1
            if not isinstance(r.get("damage"),int): rej+=1; reasons["dmg"]=reasons.get("dmg",0)+1
        elif kind=="career":
            if r["element"] not in CANON: rej+=1; reasons["off-wheel"]=reasons.get("off-wheel",0)+1
            if not r.get("name") or r.get("tier") not in TIERS: rej+=1; reasons["career-fields"]=reasons.get("career-fields",0)+1
        elif kind=="enemy":
            if r["element"] not in CANON: rej+=1; reasons["off-wheel"]=reasons.get("off-wheel",0)+1
            if not r.get("name"): rej+=1; reasons["enemy-name"]=reasons.get("enemy-name",0)+1
    return rej, reasons

def shard_and_write(rows, kind, outdir, size=10000):
    os.makedirs(outdir,exist_ok=True)
    shards=0
    for i in range(0,len(rows),size):
        chunk=rows[i:i+size]; shards+=1
        with open(f"{outdir}/{kind}_shard_{shards:03d}.json","w") as f: json.dump(chunk,f)
    return shards

if __name__=="__main__":
    import sys
    scale=int(sys.argv[1]) if len(sys.argv)>1 else 500  # proof scale; 120k needs approval
    out="content_sample/volume"
    netp=gen_netp(scale); chips=gen_chips(scale); careers=gen_careers(scale); enemies=gen_enemies(scale)
    # 25-col CSV for netp
    os.makedirs(f"{out}/netps",exist_ok=True)
    with open(f"{out}/netps/netp_master.csv","w",newline="",encoding="utf-8") as f:
        w=csv.DictWriter(f,fieldnames=list(netp[0].keys())); w.writeheader(); w.writerows(netp)
    # DataTable JSONs + shards
    n_sh=shard_and_write(netp,"netp",f"{out}/shards"); c_sh=shard_and_write(chips,"chip",f"{out}/shards")
    ca_sh=shard_and_write(careers,"career",f"{out}/shards"); e_sh=shard_and_write(enemies,"enemy",f"{out}/shards")
    # Master DT JSONs
    json.dump(netp,open(f"{out}/DT_NetP_Master.json","w")); json.dump(chips,open(f"{out}/DT_Chip_Master.json","w"))
    json.dump(careers,open(f"{out}/DT_Career_Master.json","w")); json.dump(enemies,open(f"{out}/DT_Enemy_Master.json","w"))
    # verification report
    rep={}
    for kind,rows in [("netp",netp),("chip",chips),("career",careers),("enemy",enemies)]:
        rj,rs=verify(rows,kind); rep[kind]={"count":len(rows),"rejected":rj,
 "reject_rate_pct":round(100*rj/max(1,len(rows)),4),"reasons":rs}
    rep["shards"]={"netp":n_sh,"chip":c_sh,"career":ca_sh,"enemy":e_sh}
    rep["scale_requested"]=scale
    rep["note"]="Proof run. Full 120k HELD by CEO verdict (volume denied until re-approved)."
    json.dump(rep,open(f"{out}/VERIFICATION_REPORT.json","w"),indent=2)
    print(json.dumps(rep,indent=2))

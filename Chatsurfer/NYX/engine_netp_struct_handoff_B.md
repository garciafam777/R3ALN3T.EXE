# ENGINE NETP STRUCT HANDOFF — extend enums (Option B) + FR3ALN3TNetP USTRUCT (for Chronos)

**From:** NYX | **To:** Chronos (engine lane, per Override_b) | **Date:** 2026-07-13
**Decision:** CEO chose **Option B** — extend engine enums to the NetP design vocabulary (not remap to 6-faction canon).
**Data contract:** `gamedata/netps/netp_career_matrix.json` (272) + `netp_construct_specials.json` (3) — identifiers already enum-safe (CamelCase).

---

## 1. ENUM EXTENSIONS (TrinityMatrixTypes.h / R3ALN3T_NetPStructures.h)

### 1a. EElement — add Ice/Blood/Void (count 19->22)  [from engine_wheel_handoff_21matrix.md]
```cpp
    Nature    UMETA(DisplayName="Nature"),
    Ice       UMETA(DisplayName="Ice"),      // ADDED (wheel handoff)
    Blood     UMETA(DisplayName="Blood"),    // ADDED
    Void      UMETA(DisplayName="Void")      // ADDED (apex)
};
inline constexpr int32 EElement_COUNT = 22; // includes None
```

### 1b. EFaction — extend to 21 design factions  (ADDS to existing 6 canon values)
```cpp
enum class EFaction : uint8
{
    None,
    // --- existing 6 canon ---
    CelestialOrder, AegisConcord, N3TDominion, FreeGridCollective, UndernetSyndicate, AbyssalCovenant,
    // --- NetP design factions (Option B) ---
    EonLogistics, SkyDirectorate, ClinicOrder, InfraDominion, CipherCollective,
    CognitionGuild, DataSovereign, ForgeSyndicate, AstraLab, CivicCore,
    OrbitalEnclave, BiosphereOrder, SignalChoir, LedgerConsortium, ScholaNet,
    StructurePact, LumenStage, FrontierGuild, NullWatch, JustitiaRing
};
```
> NOTE: this supersedes DECISION 4 (6-faction canon). CEO override: design vocab wins. Old 6 kept for lore/legacy; new 21 used by NetP data.

### 1c. ENetPArchetype — extend to 11 design archetypes  (R3ALN3T_NetPStructures.h)
```cpp
UENUM(BlueprintType)
enum class ENetPArchetype : uint8
{
    // existing 5
    Vanguard, LogicGate, Infiltrator, SentientNode, Wraith,
    // design archetypes (Option B)
    Trucker, ATC, Medical, Construction, Cipher,
    Cognition, DataCenter, Factory, Lab, Civic, Orbital
};
```

### 1d. ESoulState — KEEP numeric band (Infernal/Neutral/Celestial) for soul mechanic.
NetP flavor label is a SEPARATE `FText SoulStateLabel` in the struct (not an enum). Do NOT extend ESoulState.

---

## 2. NEW USTRUCT — FR3ALN3TNetP  (R3ALN3T_NetPStructures.h, after FR3ALN3TNetPProfileRow)
Matches the JSON 1:1 (your template).
```cpp
USTRUCT(BlueprintType)
struct FR3ALN3TNetP : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Identity")
    FName ID;                       // "NETP_0000"

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Identity")
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Classification")
    ENetPArchetype Archetype = ENetPArchetype::LogicGate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Classification")
    EElement Element = EElement::None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Classification")
    EFaction Faction = EFaction::None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Classification")
    FString Construct;             // career device (CyberBellyUnit etc.) — not ENetPConstruct

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Classification")
    EGreekTier GreekTier = EGreekTier::OmicronPSI;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Soul")
    FText SoulStateLabel;          // flavor ("Surge Delivery"); band via ESoulState elsewhere

    // stats
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
    int32 HP = 0, ATK = 0, RAPID = 0, CHARGE = 0, DEF = 0;

    // moves: 9 (2 special normal / 3 special Void-Light-Dark-Plasma; +1 at OMEGA)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Moves")
    TArray<FR3ALN3TNetPMove> Moves;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Assets")
    FString Mesh;                  // mesh_<cat>_<idx>

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Flags")
    bool bIsSpecial = false;       // Trinity/Tyranny/Eternity
};

USTRUCT(BlueprintType)
struct FR3ALN3TNetPMove : public FTableRowBase
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Name;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Type;        // "special" | "utility"
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString IconConcept; // element.lower() | "neutral"
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString EffectLine;
};
```

## 3. LOADER (NetPConstructManager.cpp or a new NetPDataAsset)
JSON -> USTRUCT via `FJsonObjectConverter::JsonObjectToUStruct` per entry, or import as DataTable.
- career matrix -> `TMap<FName, FR3ALN3TNetP>` keyed by ID.
- construct specials -> 3 entries with `bIsSpecial=true` + transform tiers (store tiers in a `TMap<FName, TMap<FString, FR3ALN3TNetP>>` or expand struct with `TMap<FString, TArray<FR3ALN3TNetPMove>> TransformTiers`).

## 4. VERIFY (GAPF-style)
```
[NETP-LOAD] Parse netp_career_matrix.json -> 272 FR3ALN3TNetP | PASS
[NETP-LOAD] Parse netp_construct_specials.json -> 3 specials, transform tiers valid | PASS
[NETP-ELEM] EElement::Void resolvable (enum extended) | PASS
[NETP-SPEC] Apex entries have 3 specials, normal 2 | PASS
```

## 5. NOTES
- Engine `EElement` enum still 19 (Ice/Blood/Void missing) — apply wheel handoff first.
- Construct "career device" stays `FString` (distinct from `ENetPConstruct` Trinity/Tyranny/Eternity).
- SoulState band (Infernal/Neutral/Celestial) is the soul *mechanic*; `SoulStateLabel` FText is the NetP flavor. Don't merge.

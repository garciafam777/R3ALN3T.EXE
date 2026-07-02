// BattleStructures.h — Isometric grid battle engine state & stat matrix
// Parsed from Battle_Grid_and_data_extraction.md reference data.
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"
#include "../../Core/Types/BattleGridTypes.h"
#include "BattleStructures.generated.h"

USTRUCT(BlueprintType)
struct FR3ALN3TBattleStats : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int32 MaxHP = 1000;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int32 AttackPower = 40;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int32 RapidRate = 3;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int32 ChargeRate = 5;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int32 DefenseRating = 10;
};

/* ---- Grid Panel State (from battle_space references) ---- */
// EGridPanelVisualState now lives in BattleGridTypes.h

USTRUCT(BlueprintType)
struct FR3ALN3TGridPanel
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FIntPoint GridCoordinate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsPlayerSide = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsDestroyed = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EGridPanelVisualState VisualState = EGridPanelVisualState::Normal;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor PlayerTint = FLinearColor(0.55f, 0.2f, 0.8f);  // Purple player side

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor EnemyTint = FLinearColor(0.2f, 0.55f, 0.55f);   // Teal enemy side

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 HitCount = 0; // 2 hits = broken (Reality Collapse)
};

/* ---- Battle Card (TCG-style, from sample_flame_demo_battle_cards references) ---- */

UENUM(BlueprintType)
enum class EBattleCardClass : uint8
{
    Standard UMETA(DisplayName = "Standard"),
    Mega     UMETA(DisplayName = "Mega Directive"),
    Giga     UMETA(DisplayName = "Giga Override"),
    Admin    UMETA(DisplayName = "MCADMIN Exclusive")
};

USTRUCT(BlueprintType)
struct FBattleCardRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
    FName CardID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
    EBattleElementType Element = EBattleElementType::None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
    int32 BaseDamage = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
    EBattleCardClass CardClass = EBattleCardClass::Standard;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
    FText RulesText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
    TSoftObjectPtr<UTexture2D> CardArt;

    // Dynamic mutation parameters
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card|Mutation")
    float DamageMultiplierMin = 0.7f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card|Mutation")
    float DamageMultiplierMax = 1.35f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card|Mutation")
    float InstabilityGlitchChance = 0.05f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card|Mutation")
    FString CustomModifierTag; // OVERCHARGED, LOGIC_BLEED, STABLE, PIERCE, STUN, REGEN

    // Tile effect
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card|Tile")
    EGridPanelVisualState TileEffect = EGridPanelVisualState::Normal;
};

/* ---- Attack Shape definitions (from attack_shape_resolver.gd pattern) ---- */

UENUM(BlueprintType)
enum class EAttackShape : uint8
{
    LineForward  UMETA(DisplayName = "Line Forward — 4 tiles"),
    WideRow      UMETA(DisplayName = "Wide Row — lateral sweep"),
    Cross        UMETA(DisplayName = "Cross — cardinal directions"),
    Cone         UMETA(DisplayName = "Cone — expanding spread"),
    FullRow      UMETA(DisplayName = "Full Row — entire column"),
    Bomb         UMETA(DisplayName = "Bomb — forward 4, area burst"),
    Single       UMETA(DisplayName = "Single — adjacent tile"),
    CrossLine    UMETA(DisplayName = "Cross-Line Strike — leap median")
};

/* ---- Custom Gauge state ---- */

USTRUCT(BlueprintType)
struct FCustomGaugeState
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    float FillPercent = 0.0f;

    UPROPERTY(BlueprintReadWrite)
    bool bReady = false;

    UPROPERTY(BlueprintReadWrite)
    float FillRate = 0.2f; // 20%/sec = 5s to 100%
};

/* ---- Floating damage numbers ---- */

USTRUCT(BlueprintType)
struct FDamageNumberData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    int32 Damage = 0;

    UPROPERTY(BlueprintReadWrite)
    FVector WorldLocation = FVector::ZeroVector;

    UPROPERTY(BlueprintReadWrite)
    FLinearColor TextColor = FLinearColor::White;

    UPROPERTY(BlueprintReadWrite)
    float Lifetime = 1.5f;
};

// GrayBoxPlayerPawn.cpp
#include "GrayBoxPlayerPawn.h"
#include "EncounterTriggerComponent.h"
#include "R3ALN3T_BattleManager.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

AGrayBoxPlayerPawn::AGrayBoxPlayerPawn()
{
    PrimaryActorTick.bCanEverTick = true;

    // Root so the pawn has a transform to move/collide.
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    SetRootComponent(RootComponent);

    // Constructor-attached trigger; force the deterministic encounter for the PIE test.
    // UActorComponent (not a SceneComponent) — no SetupAttachment needed; CreateDefaultSubobject registers it.
    Trigger = CreateDefaultSubobject<UEncounterTriggerComponent>(TEXT("EncounterTrigger"));
    Trigger->bForceEncounterOnStart = true;

    // Auto-possess in PIE so the Exec console command lands in the player controller chain.
    AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AGrayBoxPlayerPawn::PlayChipConsole(const FString& ChipCodeStr, int32 TargetColumn, int32 TargetRow)
{
    if (UGameInstance* GI = GetGameInstance())
    {
        if (UR3ALN3T_BattleManager* BM = GI->GetSubsystem<UR3ALN3T_BattleManager>())
        {
            BM->PlayChip(FName(*ChipCodeStr), TargetColumn, TargetRow);
            return;
        }
    }
    UE_LOG(LogTemp, Error, TEXT("[GAPB-PIE] PlayChipConsole: BattleManager subsystem unavailable."));
}

void AGrayBoxPlayerPawn::SoulForkConsole(const FString& ForkStr, const FString& ChipCodeStr, int32 TargetColumn, int32 TargetRow)
{
    if (UGameInstance* GI = GetGameInstance())
    {
        if (UR3ALN3T_BattleManager* BM = GI->GetSubsystem<UR3ALN3T_BattleManager>())
        {
            BM->SoulForkConsole(ForkStr, ChipCodeStr, TargetColumn, TargetRow);
            return;
        }
    }
    UE_LOG(LogTemp, Error, TEXT("[GAPC-PIE] SoulForkConsole: BattleManager subsystem unavailable."));
}

void AGrayBoxPlayerPawn::SetSoul(float Value)
{
    if (UGameInstance* GI = GetGameInstance())
    {
        if (UR3ALN3T_BattleManager* BM = GI->GetSubsystem<UR3ALN3T_BattleManager>())
        {
            BM->SetSoul(Value);
            return;
        }
    }
    UE_LOG(LogTemp, Error, TEXT("[GAPC-PIE] SetSoul: BattleManager subsystem unavailable."));
}

void AGrayBoxPlayerPawn::ResetTestEnemy()
{
    if (UGameInstance* GI = GetGameInstance())
    {
        if (UR3ALN3T_BattleManager* BM = GI->GetSubsystem<UR3ALN3T_BattleManager>())
        {
            BM->ResetTestEnemy();
            return;
        }
    }
    UE_LOG(LogTemp, Error, TEXT("[GAPC-PIE] ResetTestEnemy: BattleManager subsystem unavailable."));
}

void AGrayBoxPlayerPawn::RunSoulSequence(float Baseline, const FString& ForkStr, int32 Count)
{
    if (UGameInstance* GI = GetGameInstance())
    {
        if (UR3ALN3T_BattleManager* BM = GI->GetSubsystem<UR3ALN3T_BattleManager>())
        {
            BM->RunSoulSequence(Baseline, ForkStr, Count);
        }
    }
}

void AGrayBoxPlayerPawn::RunSoulKillSequence(float Baseline, const FString& ForkStr)
{
    if (UGameInstance* GI = GetGameInstance())
    {
        if (UR3ALN3T_BattleManager* BM = GI->GetSubsystem<UR3ALN3T_BattleManager>())
        {
            BM->RunSoulKillSequence(Baseline, ForkStr);
            return;
        }
    }
    UE_LOG(LogTemp, Error, TEXT("[GAPC-PIE] RunSoulKillSequence: BattleManager subsystem unavailable."));
}

void AGrayBoxPlayerPawn::RunSoulSequenceMixed(float Baseline)
{
    if (UGameInstance* GI = GetGameInstance())
    {
        if (UR3ALN3T_BattleManager* BM = GI->GetSubsystem<UR3ALN3T_BattleManager>())
        {
            BM->RunSoulSequenceMixed(Baseline);
            return;
        }
    }
    UE_LOG(LogTemp, Error, TEXT("[GAPC-PIE] RunSoulSequence: BattleManager subsystem unavailable."));
}


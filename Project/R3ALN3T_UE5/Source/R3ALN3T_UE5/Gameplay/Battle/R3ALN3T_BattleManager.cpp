#include "R3ALN3T_BattleManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

void UR3ALN3T_BattleManager::StartBattle(APlayerController* Player, const TArray<FVirusDef>& Enemies)
{
    if (bInBattle) return;
    bInBattle = true;
    BattlePlayer = Player;
    CurrentEnemies = Enemies;

    UE_LOG(LogTemp, Log, TEXT("Battle started with %d enemies"), Enemies.Num());
    OnBattleStart.Broadcast();
}

void UR3ALN3T_BattleManager::EndBattle(bool bPlayerWon)
{
    if (!bInBattle) return;
    bInBattle = false;

    PendingResult = FBattleResult();
    PendingResult.bPlayerWon = bPlayerWon;
    CalculateRewards();

    OnBattleEnd.Broadcast(PendingResult);
    UE_LOG(LogTemp, Log, TEXT("Battle ended. Player %s. Earned %d Z."),
        bPlayerWon ? TEXT("won") : TEXT("lost"), PendingResult.ZEarned);
}

void UR3ALN3T_BattleManager::CalculateRewards()
{
    if (!PendingResult.bPlayerWon) return;

    for (const auto& Virus : CurrentEnemies)
    {
        PendingResult.ZEarned += Virus.ZReward;
        PendingResult.EnemiesDefeated++;
        PendingResult.XP_Earned += 10 + Virus.HP / 10;

        if (FMath::FRand() <= Virus.DropRate && Virus.ChipDrops.Num() > 0)
        {
            int32 Index = FMath::RandRange(0, Virus.ChipDrops.Num() - 1);
            PendingResult.ChipsEarned.Add(Virus.ChipDrops[Index]);
        }
    }
}

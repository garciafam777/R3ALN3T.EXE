// R3ALN3T_UE5 GameInstance Integration: Phase 2 Core
// Player state, progression tracking, battle rewards
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../../Core/Types/MythosGameTypes.h"
#include "R3ALN3T_BattleManager.generated.h"

class ABattleGridManager;
class APlayerController;

USTRUCT(BlueprintType)
struct FVirusDef
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName VirusID;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FText DisplayName;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 HP;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Attack;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Shield;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 ZReward;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FName> ChipDrops;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) float DropRate;
};

USTRUCT(BlueprintType)
struct FBattleResult
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadOnly) bool bPlayerWon;
    UPROPERTY(BlueprintReadOnly) int32 ZEarned;
    UPROPERTY(BlueprintReadOnly) TArray<FName> ChipsEarned;
    UPROPERTY(BlueprintReadOnly) int32 XP_Earned;
    UPROPERTY(BlueprintReadOnly) int32 EnemiesDefeated;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBattleStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBattleEnd, FBattleResult, Result);

UCLASS(BlueprintType)
class R3ALN3T_UE5_API UR3ALN3T_BattleManager : public UObject
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category = "Battle")
    void StartBattle(APlayerController* Player, const TArray<FVirusDef>& Enemies);

    UFUNCTION(BlueprintCallable, Category = "Battle")
    void EndBattle(bool bPlayerWon);

    UFUNCTION(BlueprintCallable, Category = "Battle")
    bool IsInBattle() const { return bInBattle; }

    UPROPERTY(BlueprintAssignable) FOnBattleStart OnBattleStart;
    UPROPERTY(BlueprintAssignable) FOnBattleEnd OnBattleEnd;

private:
    bool bInBattle = false;
    TArray<FVirusDef> CurrentEnemies;
    APlayerController* BattlePlayer;
    void CalculateRewards();
    FBattleResult PendingResult;
};

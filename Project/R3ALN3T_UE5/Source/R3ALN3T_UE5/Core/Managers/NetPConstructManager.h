// NetPConstructManager.h — 3-NetP construct system (Nyx/engine-dev v2, Trinity Matrix canon)
// Trinity (base) / Tyranny (NG+) / Eternity (Trinity unlock at Omega rank).
#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Core/Types/TrinityMatrixTypes.h"
#include "NetPConstructManager.generated.h"

UCLASS()
class R3ALN3T_UE5_API UNetPConstructManager : public UObject
{
    GENERATED_BODY()
public:
    // Bind a construct to a career (Phase 1/2/3). Auto-sets starting tier Omicron-PSI.
    UFUNCTION(BlueprintCallable, Category="R3ALN3T|Construct")
    void BindConstruct(ENetPConstruct Construct, EFaction CareerFaction, EElement CareerElement);

    // NG+ unlock: 2nd construct (Tyranny) becomes available.
    UFUNCTION(BlueprintCallable, Category="R3ALN3T|Construct")
    bool UnlockNGPlus();

    // Trinity unlock: requires Omega rank on any bound NetP (Phase 3).
    UFUNCTION(BlueprintCallable, Category="R3ALN3T|Construct")
    bool UnlockTrinity(EGreekTier HighestRank);

    UFUNCTION(BlueprintPure, Category="R3ALN3T|Construct")
    int32 ActiveConstructCount() const { return static_cast<int32>(Bound.Num()); }

protected:
    UPROPERTY() TMap<ENetPConstruct, FR3ALN3TNetPStatus> Bound;
    bool bNGPlus = false;
    bool bTrinity = false;
};

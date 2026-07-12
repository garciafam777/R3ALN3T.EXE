// NetPConstructManager.cpp — 3-NetP construct system (Nyx/engine-dev v2)
#include "NetPConstructManager.h"

void UNetPConstructManager::BindConstruct(ENetPConstruct Construct, EFaction CareerFaction, EElement CareerElement)
{
    if (Bound.Contains(Construct)) return;
    FR3ALN3TNetPStatus S;
    S.Tier = EGreekTier::OmicronPSI;     // every new NetP starts at floor
    S.FactionLean = CareerFaction;
    S.Element = CareerElement;
    S.Construct = Construct;
    Bound.Add(Construct, S);
}

bool UNetPConstructManager::UnlockNGPlus()
{
    // Phase 2: base game complete -> 2nd construct allowed.
    if (bNGPlus) return false;
    bNGPlus = true;
    return true; // caller binds Tyranny next
}

bool UNetPConstructManager::UnlockTrinity(EGreekTier HighestRank)
{
    // Phase 3: Omega rank on any NetP -> 3rd construct (Eternity).
    if (bTrinity) return false;
    if (HighestRank < EGreekTier::Omega) return false;
    bTrinity = true;
    return true; // caller binds Eternity next
}

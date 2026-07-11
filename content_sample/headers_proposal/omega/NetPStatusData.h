// NetPStatusData.h - NetP status incl. 3 OMEGA supremacy fields (PROPOSAL, Nyx/DevOps)
// REVIEW-ONLY. Extends the verified 25-col NetP with supremacy_tier / domain_element /
// covenant_state per OMEGA Overlord spec.
#pragma once
#include "CoreMinimal.h"
#include "NetPTypes.h"
#include "NetPStatusData.generated.h"

USTRUCT(BlueprintType)
struct FNetPStatusData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString NetPId;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString DisplayName;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) EElement Element;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) ECareerTier CareerTier;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 CSI; // 0-100 (clamped; see prior fix)
    UPROPERTY(EditAnywhere, BlueprintReadWrite) ESupremacyTier SupremacyTier;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) EElement DomainElement; // OMEGA ELEMENTAL claims this; PRIME uses Void-by-convention (see flag)
    UPROPERTY(EditAnywhere, BlueprintReadWrite) ECovenantState CovenantState;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString FlavorText;
    // ... existing 25-column fields (card_number,tier,rank,name,alignment,element,
    //     faction,hp,atk,rapid,charge,defense,move_1..9,construct_sprite,
    //     source_identities,color_pal) continue here, same as NetP.h ...
};

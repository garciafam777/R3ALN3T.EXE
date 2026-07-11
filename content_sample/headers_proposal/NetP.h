// NetP.h - MMBN-style NetNavi profile struct (25 fields, matches content_sample netp_sample.csv)
// PROPOSAL (Nyx/DevOps) - for Chatsurfer review; NOT yet in Source/.
#pragma once
#include "CoreMinimal.h"
#include "NetP.generated.h"

UENUM(BlueprintType)
enum class ENetPTier : uint8
{
    OMEGA, ALPHA, BETA, GAMMA, DELTA, EPSILON, ZETA, ETA,
    THETA, IOTA, KAPPA, LAMBDA, MU, NU, XI, OMICRON
};

UENUM(BlueprintType)
enum class ENetPAlignment : uint8
{
    Mechanical, Viral, Angelic, Demonic
};

UENUM(BlueprintType)
enum class ENetPElement : uint8   // canonical 7-wheel (BattleGridTypes.h:19)
{
    None, Fire, Aqua, Elec, Wood, Wind, Holy, Void
};

USTRUCT(BlueprintType)
struct FR3ALN3TNetP
{
    GENERATED_BODY()

    // identity
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString CardNumber;   // card_number
    UPROPERTY(EditAnywhere, BlueprintReadWrite) ENetPTier Tier;       // tier
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Rank;           // rank
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Name;         // name
    UPROPERTY(EditAnywhere, BlueprintReadWrite) ENetPAlignment Alignment; // alignment
    UPROPERTY(EditAnywhere, BlueprintReadWrite) ENetPElement Element; // element
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Faction;     // faction

    // stats
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 HP;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 ATK;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Rapid;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Charge;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Defense;

    // moves (1..9)
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Move01;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Move02;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Move03;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Move04;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Move05;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Move06;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Move07;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Move08;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Move09;

    // meta
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString FlavorText;       // flavor_text
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString ConstructSprite;   // construct_sprite
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString SourceIdentities;  // source_identities
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString ColorPal;          // color_pal
};

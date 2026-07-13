// BattleChipTypes.h
// Core data types for the Greek-letter chip-code system (MMBN-style code-share rule).
#pragma once
#include "CoreMinimal.h"
#include "BattleChipTypes.generated.h"

// 24 Greek letters used as chip "codes." A chip with code "Omega" and a chip with
// code "Alpha" CANNOT be selected into the same hand together, unless one of them
// is the wildcard code (EChipCode::Star), which combos with anything.
UENUM(BlueprintType)
enum class EChipCode : uint8
{
	Alpha, Beta, Gamma, Delta, Epsilon, Zeta, Eta, Theta,
	Iota, Kappa, Lambda, Mu, Nu, Xi, Omicron, Pi,
	Rho, Sigma, Tau, Upsilon, Phi, Chi, Psi, Omega,
	Star UMETA(DisplayName = "* (Wildcard)") // combos with any code, MMBN "*" code equivalent
};

UENUM(BlueprintType)
enum class EChipClass : uint8
{
	Standard,
	Mega,
	Giga,
	SecretArt // top-tier rare, usually single-letter-locked, e.g. Trinity Ascendant's "Resurrection"
};

USTRUCT(BlueprintType)
struct FBattleChip : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ChipID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EChipCode Code = EChipCode::Alpha;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EChipClass Class = EChipClass::Standard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Power = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EElementType Element = EElementType::None;

	// How many copies of this exact chip+code pair are allowed in one folder (MMBN rule: max 4 normal, 1 Mega, 1 Giga)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxCopiesInFolder = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon = nullptr;
};

// A single physical copy sitting in a folder/hand — same ChipID can repeat with different codes
USTRUCT(BlueprintType)
struct FChipInstance
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ChipID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EChipCode Code = EChipCode::Alpha;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGuid InstanceGuid; // unique per physical copy, so duplicates don't collide in selection logic

	FChipInstance()
	{
		InstanceGuid = FGuid::NewGuid();
	}
};

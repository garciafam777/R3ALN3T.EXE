// R3ALN3T_DeveloperSettings.h
// Phase1-A2: Global System Registration.
// Centralizes balance/grid/element constants previously scattered as file-static
// constexprs, so they are tunable from Project Settings / DefaultGame.ini WITHOUT
// a recompile (UDeveloperSettings + config specifier = ini-driven, hot-reloadable).
#pragma once
#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "R3ALN3T_DeveloperSettings.generated.h"

UCLASS(config=Game, defaultconfig, meta=(DisplayName="R3ALN3T Developer Settings"))
class R3ALN3T_UE5_API UR3ALN3T_DeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UR3ALN3T_DeveloperSettings();

	// --- ZETA power envelope (was PlayChipPowerCeiling in R3ALN3T_BattleManager.cpp) ---
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category="Balance|Zeta",
		meta=(ClampMin="0", ClampMax="9999"))
	float PlayChipPowerCeiling = 120.f;

	// --- Grid constraints (was static constexpr in BattleGridManager.h) ---
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category="Grid")
	int32 GridCols = 8;
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category="Grid")
	int32 GridRows = 4;
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category="Grid")
	int32 MedianCol = 4; // enemy-spawn gate: cols [MedianCol, GridCols) are hostile

	// --- Element canon (was CanonElementLast in NetPRandomizer.cpp) ---
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category="Elements")
	int32 CanonElementFirst = 1;  // EElement::Fire
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category="Elements")
	int32 CanonElementLast = 21;  // EElement::Void

	// Single authoritative accessor (cached pointer; UDeveloperSettings is a singleton).
	static const UR3ALN3T_DeveloperSettings* Get();
};

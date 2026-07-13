// World registry structs — region/country data tables (CEO task #2: 12-country/5-region registry).
// Additive: new file, no edits to shared headers. Canon source: Docs/Roads/lands.md (post-Fall PR, 3 biomes).
// Gap reported honestly: canon yields 3 PR regions, 0 named sovereign nations beyond the island.
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "WorldRegistryTypes.generated.h"

USTRUCT(BlueprintType)
struct FRegionRegistryRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World|Region")
	FName RegionID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World|Region")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World|Region")
	FText Description;

	// Macro-region grouping (canon has 1: post-Fall Puerto Rico). "Global" reserved for future.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World|Region")
	FName MacroRegion = FName("PuertoRicoPostFall");

	// Elevation band relative to new ocean floor (m). From lands.md biome defs.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World|Region")
	float ElevationMinM = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World|Region")
	float ElevationMaxM = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World|Region")
	bool bCanonSeeded = false; // true = traced to lands.md; false = placeholder/proposed
};

USTRUCT(BlueprintType)
struct FCountryRegistryRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World|Country")
	FName CountryID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World|Country")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World|Country")
	FName HomeRegionID; // FK to FRegionRegistryRow

	// Canon names 0 sovereign nations beyond PR itself. Set true only when lore actually names one.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World|Country")
	bool bCanonNamed = false;
};

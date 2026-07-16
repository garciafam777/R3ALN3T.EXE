// R3ALN3T_DeveloperSettings.cpp
// Phase1-A2: single-source balance/grid/element constants.
#include "R3ALN3T_DeveloperSettings.h"
#include "Internationalization/Internationalization.h"

UR3ALN3T_DeveloperSettings::UR3ALN3T_DeveloperSettings()
	: PlayChipPowerCeiling(120.f)
	, GridCols(8)
	, GridRows(4)
	, MedianCol(4)
	, CanonElementFirst(1)
	, CanonElementLast(21)
{
}

const UR3ALN3T_DeveloperSettings* UR3ALN3T_DeveloperSettings::Get()
{
	// UDeveloperSettings singleton — safe to call from any gameplay thread after init.
	return GetDefault<UR3ALN3T_DeveloperSettings>();
}

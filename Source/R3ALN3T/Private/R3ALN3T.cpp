#include "Modules/ModuleManager.h"
#include "R3ALN3T.h"

class FR3ALN3TModule : public IModuleInterface
{
public:
	virtual void StartupModule() override {}
	virtual void ShutdownModule() override {}
};

IMPLEMENT_PRIMARY_GAME_MODULE(FDefaultGameModuleImpl, R3ALN3T, "R3ALN3T");

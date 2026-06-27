#include "R3ALN3TGameModeBase.h"
#include "R3ALN3TCharacter.h"

AR3ALN3TGameModeBase::AR3ALN3TGameModeBase()
{
	// Set C++ character as default pawn
	DefaultPawnClass = AR3ALN3TCharacter::StaticClass();
}

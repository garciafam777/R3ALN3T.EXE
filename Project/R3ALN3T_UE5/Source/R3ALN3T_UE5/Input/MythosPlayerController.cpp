#include "MythosPlayerController.h"

#include "Engine/World.h"
#include "InputCoreTypes.h"
#include "../Gameplay/Narrative/MythosGameMode.h"
#include "../Gameplay/Battle/R3ALN3T_BattleManager.h"       // Gap D: UR3ALN3T_BattleManager
#include "../Core/Managers/R3ALN3TGameInstance.h"           // Gap D: UR3ALN3TGameInstance

void AMythosPlayerController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;
	SetInputMode(FInputModeGameAndUI());
}

void AMythosPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindKey(EKeys::One, IE_Pressed, this, &AMythosPlayerController::PressOne);
	InputComponent->BindKey(EKeys::Two, IE_Pressed, this, &AMythosPlayerController::PressTwo);
	InputComponent->BindKey(EKeys::Three, IE_Pressed, this, &AMythosPlayerController::PressThree);
	InputComponent->BindKey(EKeys::Four, IE_Pressed, this, &AMythosPlayerController::PressFour);
	InputComponent->BindKey(EKeys::Five, IE_Pressed, this, &AMythosPlayerController::PressFive);
	InputComponent->BindKey(EKeys::Six, IE_Pressed, this, &AMythosPlayerController::PressSix);
	InputComponent->BindKey(EKeys::R, IE_Pressed, this, &AMythosPlayerController::PressR);
	InputComponent->BindKey(EKeys::SpaceBar, IE_Pressed, this, &AMythosPlayerController::PressSpace);
	InputComponent->BindKey(EKeys::Enter, IE_Pressed, this, &AMythosPlayerController::PressEnter);
}

void AMythosPlayerController::PressOne() { HandleNumber(1); }
void AMythosPlayerController::PressTwo() { HandleNumber(2); }
void AMythosPlayerController::PressThree() { HandleNumber(3); }
void AMythosPlayerController::PressFour() { HandleNumber(4); }
void AMythosPlayerController::PressFive() { HandleNumber(5); }
void AMythosPlayerController::PressSix() { HandleNumber(6); }

void AMythosPlayerController::PressR()
{
	if (AMythosGameMode* GM = GetWorld()->GetAuthGameMode<AMythosGameMode>())
	{
		GM->NewRun();
	}
}

void AMythosPlayerController::PressSpace()
{
	if (AMythosGameMode* GM = GetWorld()->GetAuthGameMode<AMythosGameMode>())
	{
		if (GM->Run.Screen == EMythosScreen::Work)
		{
			GM->WorkShift();
		}
		else if (GM->Run.Screen == EMythosScreen::Ending)
		{
			GM->ResolveEndingByIndex(-1);
		}
	}
}

void AMythosPlayerController::PressEnter()
{
	if (AMythosGameMode* GM = GetWorld()->GetAuthGameMode<AMythosGameMode>())
	{
		if (GM->Run.Screen == EMythosScreen::Start)
		{
			GM->Run.Screen = EMythosScreen::CareerSelect;
			GM->Run.Objective = TEXT("Choose a career with 1-6.");
		}
		else if (GM->Run.Screen == EMythosScreen::Work && GM->Run.Day >= 3)
		{
			GM->EnterCurrentStoryNode();
		}
	}
}

void AMythosPlayerController::HandleNumber(int32 Number)
{
	AMythosGameMode* GM = GetWorld()->GetAuthGameMode<AMythosGameMode>();
	if (!GM) return;

	const int32 Index = Number - 1;
	switch (GM->Run.Screen)
	{
	case EMythosScreen::Start:
		GM->Run.Screen = EMythosScreen::CareerSelect;
		GM->Run.Objective = TEXT("Choose a career with 1-6.");
		break;
	case EMythosScreen::CareerSelect:
		GM->ChooseCareerByIndex(Index);
		break;
	case EMythosScreen::ElementSelect:
		GM->ChooseElementByIndex(Index);
		break;
	case EMythosScreen::Work:
		if (Number == 1) GM->WorkShift();
		if (Number == 2 && GM->Run.Day >= 3) GM->EnterCurrentStoryNode();
		break;
	case EMythosScreen::StoryChoice:
		GM->ChooseStoryOption(Index);
		break;
	case EMythosScreen::Battle:
		if (Index >= 0 && Index < 4) GM->ResolveBattleAction(static_cast<EMythosBattleAction>(Index));
		break;
	case EMythosScreen::Ending:
		if (Index >= 0 && Index < 6) GM->ResolveEndingByIndex(Index);
		break;
	case EMythosScreen::PostGame:
		if (Index >= 0 && Index < 3) GM->PostGameAction(Index);
		break;
	default:
		break;
	}
}

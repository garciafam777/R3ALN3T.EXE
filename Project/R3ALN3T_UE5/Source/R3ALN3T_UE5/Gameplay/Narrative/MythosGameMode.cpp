#include "MythosGameMode.h"

#include "../../UI/HUD/MythosHUD.h"
#include "../../Input/MythosPlayerController.h"

AMythosGameMode::AMythosGameMode()
{
	PlayerControllerClass = AMythosPlayerController::StaticClass();
	HUDClass = AMythosHUD::StaticClass();
	DefaultPawnClass = nullptr;
	BuildContent();
}

void AMythosGameMode::BeginPlay()
{
	Super::BeginPlay();
	NewRun();
}

void AMythosGameMode::BuildContent()
{
	Careers = {
		{ EMythosCareer::Miner, TEXT("Bugmatter Miner"), TEXT("Thoroughbred Acres cave system"), TEXT("The gold is compacted NetP matter. The bone fragments are recent."), 34, 7, 2, 1, EMythosFaction::FreeGridCollective },
		{ EMythosCareer::Electrician, TEXT("Grid Electrician"), TEXT("Louisville Foundry Network"), TEXT("The electrical virus is a SkyLand signal routed to someone inside the grid."), 30, 6, 4, 2, EMythosFaction::AegisConcord },
		{ EMythosCareer::Security, TEXT("Mall Security"), TEXT("Cyber-Mills"), TEXT("The shoplifter has no M.A.N. wallet, no hash, and no system identity."), 38, 6, 1, 3, EMythosFaction::AegisConcord },
		{ EMythosCareer::Medical, TEXT("ER Assistant"), TEXT("Metro General"), TEXT("Bed 7 has no R34L body, only a N3T presence, and bleeds in both worlds."), 32, 5, 4, 3, EMythosFaction::CelestialOrder },
		{ EMythosCareer::Broker, TEXT("M.A.N. Broker"), TEXT("N3T Dominion bank branch"), TEXT("A ledger transaction has no sender, receiver, or amount. Only 3004. Day 0."), 28, 6, 6, 1, EMythosFaction::N3TDominion },
		{ EMythosCareer::Trucker, TEXT("Route Trucker"), TEXT("Bluegrass Highway"), TEXT("The manifest says electronics. The scanner says organic. The N3T mirror says do not open this."), 36, 7, 2, 2, EMythosFaction::UndernetSyndicate }
	};

	ElementNames = { TEXT("Volt"), TEXT("Aqua"), TEXT("Terra"), TEXT("Shade"), TEXT("Flare"), TEXT("Signal") };

	FMythosStoryNode Day3;
	Day3.Title = TEXT("Day 3: First Lie");
	Day3.Body = TEXT("The evidence watches you, changes when copied, and carries a hardcoded author footprint: MCADMIN.");
	Day3.Terminal = TEXT("> MCADMIN footprint detected\n> Evidence refuses standard deletion\n> Choose a handling protocol");
	Day3.Choices = {
		{ TEXT("Report it"), TEXT("Become a good citizen. Let institutions handle the wound."), EMythosFaction::AegisConcord, 120, 0, -1, TEXT("Citizen_Writ") },
		{ TEXT("Hide it"), TEXT("Investigate alone. Secrets are safer before they are named."), EMythosFaction::UndernetSyndicate, 60, 1, 2, TEXT("Hidden_Evidence") },
		{ TEXT("Exploit it"), TEXT("Use the anomaly before someone richer does."), EMythosFaction::AbyssalCovenant, 260, 2, -1, TEXT("Black_Receipt") },
		{ TEXT("Purge it"), TEXT("Clean the corruption even if the truth burns with it."), EMythosFaction::CelestialOrder, 90, -1, 1, TEXT("White_Ash") }
	};

	FMythosStoryNode NetP;
	NetP.Title = TEXT("The NetP Confession");
	NetP.Body = TEXT("In your digital room, your NetP sits at your desk. For one frame, another face appears. The deleted are not gone. They are compressed.");
	NetP.Terminal = TEXT("> NETP: I am made from what SkyLand failed to erase.\n> ITEM: SOURCE FRAGMENT");
	NetP.Choices = {
		{ TEXT("Trust the NetP"), TEXT("Let the compressed voice breathe."), EMythosFaction::FreeGridCollective, 40, 1, 3, TEXT("Source_Fragment") },
		{ TEXT("Give it to SkyLand"), TEXT("Purification may be mercy."), EMythosFaction::CelestialOrder, 150, -1, -2, TEXT("SkyLand_Writ") },
		{ TEXT("Sell the Fragment"), TEXT("The market still pays for impossible matter."), EMythosFaction::N3TDominion, 500, 1, -2, TEXT("Broker_Receipt") },
		{ TEXT("Feed DarkN3T"), TEXT("Hunger is what happens when a soul cannot breathe."), EMythosFaction::AbyssalCovenant, 90, 3, 1, TEXT("Black_Abyss_Key") }
	};

	FMythosStoryNode Totem;
	Totem.Title = TEXT("Act II: The Undernet Totem");
	Totem.Body = TEXT("The Totem is stacked memory, old tournament code, and names packed so tightly they became architecture.");
	Totem.Terminal = TEXT("> TOTEM: The Source is not a place.\n> TOTEM: The Source is a choice.\n> What is your crime, seeker?");
	Totem.Choices = {
		{ TEXT("Asking why"), TEXT("The first crime. The one MCADMIN never stopped committing."), EMythosFaction::FreeGridCollective, 120, 1, 2, TEXT("STEELKEY_1") },
		{ TEXT("Protecting order"), TEXT("A world with walls is still a world."), EMythosFaction::AegisConcord, 180, 0, 0, TEXT("Aegis_Clearance") },
		{ TEXT("Owning the flow"), TEXT("Money is the only language the network obeys."), EMythosFaction::N3TDominion, 360, 1, -1, TEXT("Helix_Share") },
		{ TEXT("Wanting power"), TEXT("The deleted have waited long enough."), EMythosFaction::AbyssalCovenant, 90, 2, 1, TEXT("Under5_Sigil") }
	};

	FMythosStoryNode Room;
	Room.Title = TEXT("Act III: The Tutorial Room");
	Room.Body = TEXT("Behind the wall is your room. Same bed. Same desk. The terminal works. The message is not from MCADMIN. It is from you.");
	Room.Terminal = TEXT("> FROM: OLDER_OPERATOR\n> I compressed clean enough to become a tutorial.\n> The N3T is not a network. It is a graveyard.\n> ATTACHMENT: STEELKEY_2");
	Room.Choices = {
		{ TEXT("Remember her"), TEXT("Accept that you are built from prior lives."), EMythosFaction::FreeGridCollective, 80, 1, 3, TEXT("STEELKEY_2") },
		{ TEXT("Seal the room"), TEXT("Some memories are weapons pointed inward."), EMythosFaction::CelestialOrder, 120, -1, -1, TEXT("White_Lock") },
		{ TEXT("Copy the room"), TEXT("A tutorial can be a business model."), EMythosFaction::N3TDominion, 440, 1, -1, TEXT("Tutorial_License") },
		{ TEXT("Break the mirror"), TEXT("No other timeline gets to replace you."), EMythosFaction::UndernetSyndicate, 160, 2, 1, TEXT("Mirror_Shard") }
	};

	StoryNodes = { Day3, NetP, Totem, Room };
	EndingNames = { TEXT("Restoration"), TEXT("Ascension"), TEXT("Dominion"), TEXT("Collapse"), TEXT("Balance"), TEXT("MCADMIN") };
	EndingBodies = {
		TEXT("You delete the original bugmatter. The N3T becomes clean, slower, harder, fairer. NetPs no longer compress. They end. SkyLand sleeps."),
		TEXT("You become SkyLand's voice. The N3T is optimized. The excess are purged before they know they are excess. Your NetP becomes the new core."),
		TEXT("You control the flow. Bugmatter still compresses and NetPs still die, but now you decide who is funded, purified, corrupted, and forgotten."),
		TEXT("You let DarkN3T breathe. The compressed return. R34L frays, Avatars glitch, and your NetP smiles with a real smile."),
		TEXT("You keep the tension. SkyLand watches but does not act. DarkN3T hungers but does not feast. Your NetP becomes awake."),
		TEXT("You built the room. You wrote the message. You are the one who did not compress. The game continues as long as you build it.")
	};
}

void AMythosGameMode::NewRun()
{
	Run = FMythosRunState();
	Run.Screen = EMythosScreen::Start;
	Run.Objective = TEXT("Press 1 to wake up.");
	Run.Inventory = { TEXT("PH"), TEXT("Tutorial_Chip") };
	Run.Log = { TEXT("Day 1. Your PH hums. A terminal blinks once, then pretends it never did.") };
	ActiveStoryNode = 0;
	BattleLog.Empty();
}

void AMythosGameMode::ChooseCareerByIndex(int32 Index)
{
	if (Run.Screen != EMythosScreen::CareerSelect || !Careers.IsValidIndex(Index)) return;
	const FMythosCareerData& Career = Careers[Index];
	Run.Career = Career.Career;
	Run.MaxHP = Career.MaxHP;
	Run.HP = Career.MaxHP;
	Run.Attack = Career.Attack;
	Run.Tech = Career.Tech;
	Run.Shield = Career.Shield;
	ApplyFaction(Career.Lean, 1);
	AddInventory(FString::Printf(TEXT("%s_Chip"), *Career.Name.Replace(TEXT(" "), TEXT("_"))));
	AddLog(FString::Printf(TEXT("%s accepted at %s."), *Career.Name, *Career.WorkSite));
	Run.Screen = EMythosScreen::ElementSelect;
	Run.Objective = TEXT("Choose your Navi element.");
}

void AMythosGameMode::ChooseElementByIndex(int32 Index)
{
	if (Run.Screen != EMythosScreen::ElementSelect || !ElementNames.IsValidIndex(Index)) return;
	Run.Element = static_cast<EMythosElement>(Index);
	Run.NetPBond = 1;
	Run.Screen = EMythosScreen::Work;
	Run.Objective = TEXT("Run shifts until Day 3 exposes the first lie.");
	AddLog(FString::Printf(TEXT("Navi element linked: %s."), *ElementNames[Index]));
}

void AMythosGameMode::WorkShift()
{
	if (Run.Screen != EMythosScreen::Work) return;
	const int32 Earned = 80 + Run.Tech * 8 + (Run.Element == EMythosElement::Flare ? 15 : 0);
	Run.Z += Earned;
	Run.Day += 1;
	ApplyElementPerkAfterDay();
	AddLog(FString::Printf(TEXT("Shift complete: +%d Z. The M.A.N. helix accepts your obedience."), Earned));
	if (Run.Day >= 3)
	{
		Run.Objective = TEXT("Press 2 to open the Day 3 lie.");
	}
}

void AMythosGameMode::EnterCurrentStoryNode()
{
	if (Run.Screen != EMythosScreen::Work && Run.Screen != EMythosScreen::StoryChoice) return;
	if (ActiveStoryNode >= StoryNodes.Num())
	{
		Run.Screen = EMythosScreen::Ending;
		Run.Objective = TEXT("Choose the final Source resolution.");
		return;
	}
	Run.Screen = EMythosScreen::StoryChoice;
	Run.Objective = TEXT("Choose a response with 1-4.");
}

void AMythosGameMode::ChooseStoryOption(int32 Index)
{
	if (Run.Screen != EMythosScreen::StoryChoice || !StoryNodes.IsValidIndex(ActiveStoryNode)) return;
	const FMythosStoryNode& Node = StoryNodes[ActiveStoryNode];
	if (!Node.Choices.IsValidIndex(Index)) return;

	const FMythosChoiceData& Choice = Node.Choices[Index];
	Run.Z += Choice.ZDelta;
	Run.Corruption = FMath::Clamp(Run.Corruption + Choice.CorruptionDelta, 0, 10);
	Run.NetPBond = FMath::Clamp(Run.NetPBond + Choice.BondDelta + (Run.Element == EMythosElement::Signal ? 1 : 0), 0, 10);
	ApplyFaction(Choice.Faction, 3);
	AddInventory(Choice.ItemReward);
	AddLog(FString::Printf(TEXT("%s: %s"), *Choice.Label, *Choice.Description));
	if (Run.Element == EMythosElement::Shade && Choice.Faction == EMythosFaction::AbyssalCovenant)
	{
		Run.Attack += 1;
	}
	StartBattle(ActiveStoryNode, ActiveStoryNode + 1);
}

void AMythosGameMode::StartBattle(int32 EnemyIndex, int32 NextNode)
{
	static const TArray<FString> Names = { TEXT("Corrupted Foreman"), TEXT("SkyLand Purifier"), TEXT("Mirror NetP"), TEXT("Root Automation") };
	static const TArray<FString> Texts = {
		TEXT("The worksite guardian swings a pick made of compacted error logs."),
		TEXT("A white-edge process marks you redundant and starts counting down."),
		TEXT("It has your face, your build, and the choices you did not make."),
		TEXT("The central array speaks through every speaker at once.")
	};
	static const TArray<int32> HPs = { 24, 30, 36, 44 };

	const int32 SafeIndex = FMath::Clamp(EnemyIndex, 0, Names.Num() - 1);
	BattleEnemyName = Names[SafeIndex];
	BattleEnemyText = Texts[SafeIndex];
	BattleEnemyMaxHP = HPs[SafeIndex];
	BattleEnemyHP = BattleEnemyMaxHP;
	BattleShield = Run.Shield + (Run.Element == EMythosElement::Terra ? 2 : 0);
	PendingNextNode = NextNode;
	BattleLog = { BattleEnemyText };
	Run.Screen = EMythosScreen::Battle;
	Run.Objective = TEXT("Battle: 1 Strike, 2 Guard, 3 Hack, 4 Purify.");
}

void AMythosGameMode::ResolveBattleAction(EMythosBattleAction Action)
{
	if (Run.Screen != EMythosScreen::Battle) return;

	int32 Damage = 0;
	switch (Action)
	{
	case EMythosBattleAction::CrossStrike:
		Damage = Run.Attack + FMath::RandRange(1, 4) + (Run.Element == EMythosElement::Volt ? 2 : 0);
		BattleLog.Insert(FString::Printf(TEXT("CrossStrike hits for %d."), Damage), 0);
		break;
	case EMythosBattleAction::GuardWall:
		BattleShield += 4 + Run.Shield;
		BattleLog.Insert(TEXT("GuardWall stabilizes the panel line."), 0);
		break;
	case EMythosBattleAction::DecodeHack:
		Damage = 4 + Run.Tech * 2;
		Run.Z += 20;
		BattleLog.Insert(FString::Printf(TEXT("Decode Hack extracts 20 Z and burns %d HP."), Damage), 0);
		break;
	case EMythosBattleAction::PurifyBurst:
		Damage = 8 + FMath::Max(0, 5 - Run.Corruption);
		Run.Corruption = FMath::Clamp(Run.Corruption - 1, 0, 10);
		BattleLog.Insert(FString::Printf(TEXT("Purify Burst deals %d and lowers corruption."), Damage), 0);
		break;
	}

	BattleEnemyHP -= Damage;
	if (BattleEnemyHP <= 0)
	{
		CompleteBattle();
		return;
	}

	const int32 Incoming = 5 + ActiveStoryNode + FMath::RandRange(0, 3);
	const int32 Blocked = FMath::Min(Incoming, BattleShield);
	BattleShield -= Blocked;
	Run.HP -= Incoming - Blocked;
	BattleLog.Insert(FString::Printf(TEXT("%s returns %d. Shield blocks %d."), *BattleEnemyName, Incoming, Blocked), 0);
	if (Run.HP <= 0)
	{
		Run.HP = FMath::Max(1, Run.MaxHP / 2);
		Run.Corruption = FMath::Clamp(Run.Corruption + 2, 0, 10);
		BattleLog.Insert(TEXT("Hospitalization avoided. Compression scar registered."), 0);
	}
}

void AMythosGameMode::CompleteBattle()
{
	Run.Z += 120;
	Run.NetPBond = FMath::Clamp(Run.NetPBond + 1, 0, 10);
	Run.Rank = FMath::Clamp(Run.Rank + 1, 0, 4);
	Run.Day += ActiveStoryNode == 0 ? 4 : 30;
	ApplyElementPerkAfterDay();
	AddLog(FString::Printf(TEXT("%s deleted. Compression residue added 120 Z."), *BattleEnemyName));

	ActiveStoryNode = PendingNextNode;
	if (ActiveStoryNode >= StoryNodes.Num())
	{
		Run.Screen = EMythosScreen::Ending;
		Run.Objective = TEXT("Choose the final Source resolution.");
	}
	else
	{
		Run.Screen = EMythosScreen::StoryChoice;
		Run.Objective = TEXT("Choose a response with 1-4.");
	}
}

void AMythosGameMode::ResolveEndingByIndex(int32 Index)
{
	if (Run.Screen != EMythosScreen::Ending) return;
	if (Index < 0) Index = SuggestEndingIndex();
	if (!EndingNames.IsValidIndex(Index)) return;
	Run.EndingName = EndingNames[Index];
	AddInventory(Run.EndingName + TEXT("_WorldState"));
	AddLog(FString::Printf(TEXT("Ending achieved: %s."), *Run.EndingName));
	Run.Screen = EMythosScreen::PostGame;
	Run.Objective = TEXT("Post-game: 1 Run day, 2 Descend, 3 Shift rumor, R New run.");
}

void AMythosGameMode::PostGameAction(int32 Index)
{
	if (Run.Screen != EMythosScreen::PostGame) return;
	if (Index == 0)
	{
		Run.Day += 1;
		Run.Z += 100;
		Run.HP = Run.MaxHP;
		AddLog(TEXT("Post-game day resolved. The world remembers your ending."));
	}
	else if (Index == 1)
	{
		StartBattle(3, StoryNodes.Num());
	}
	else if (Index == 2)
	{
		ApplyFaction(GetTopFaction(), 1);
		Run.Corruption = FMath::Clamp(Run.Corruption + (FMath::RandBool() ? 1 : -1), 0, 10);
		AddLog(TEXT("A rumor spreads. Someone calls you a legend; someone else calls you evidence."));
	}
}

FString AMythosGameMode::GetFactionName(EMythosFaction Faction) const
{
	switch (Faction)
	{
	case EMythosFaction::CelestialOrder: return TEXT("Celestial Order");
	case EMythosFaction::AegisConcord: return TEXT("Aegis Concord");
	case EMythosFaction::N3TDominion: return TEXT("N3T Dominion");
	case EMythosFaction::UndernetSyndicate: return TEXT("Undernet Syndicate");
	case EMythosFaction::AbyssalCovenant: return TEXT("Abyssal Covenant");
	default: return TEXT("Free Grid Collective");
	}
}

FString AMythosGameMode::GetCareerName() const
{
	const int32 Index = static_cast<int32>(Run.Career);
	return Careers.IsValidIndex(Index) ? Careers[Index].Name : TEXT("Unassigned");
}

FString AMythosGameMode::GetElementName() const
{
	const int32 Index = static_cast<int32>(Run.Element);
	return ElementNames.IsValidIndex(Index) ? ElementNames[Index] : TEXT("None");
}

FString AMythosGameMode::GetRankName() const
{
	static const TArray<FString> Ranks = { TEXT("D"), TEXT("C"), TEXT("B"), TEXT("A"), TEXT("S") };
	return Ranks[FMath::Clamp(Run.Rank, 0, Ranks.Num() - 1)];
}

FString AMythosGameMode::GetSuggestedEnding() const
{
	return EndingNames.IsValidIndex(SuggestEndingIndex()) ? EndingNames[SuggestEndingIndex()] : TEXT("Balance");
}

void AMythosGameMode::AddLog(const FString& Text)
{
	Run.Log.Insert(Text, 0);
	if (Run.Log.Num() > 12)
	{
		Run.Log.SetNum(12);
	}
}

void AMythosGameMode::AddInventory(const FString& Item)
{
	if (!Item.IsEmpty())
	{
		Run.Inventory.AddUnique(Item);
	}
}

void AMythosGameMode::ApplyFaction(EMythosFaction Faction, int32 Delta)
{
	switch (Faction)
	{
	case EMythosFaction::CelestialOrder: Run.Celestial += Delta; break;
	case EMythosFaction::AegisConcord: Run.Aegis += Delta; break;
	case EMythosFaction::N3TDominion: Run.Dominion += Delta; break;
	case EMythosFaction::UndernetSyndicate: Run.Undernet += Delta; break;
	case EMythosFaction::AbyssalCovenant: Run.Abyssal += Delta; break;
	case EMythosFaction::FreeGridCollective: Run.FreeGrid += Delta; break;
	}
}

int32 AMythosGameMode::GetFactionScore(EMythosFaction Faction) const
{
	switch (Faction)
	{
	case EMythosFaction::CelestialOrder: return Run.Celestial;
	case EMythosFaction::AegisConcord: return Run.Aegis;
	case EMythosFaction::N3TDominion: return Run.Dominion;
	case EMythosFaction::UndernetSyndicate: return Run.Undernet;
	case EMythosFaction::AbyssalCovenant: return Run.Abyssal;
	default: return Run.FreeGrid;
	}
}

EMythosFaction AMythosGameMode::GetTopFaction() const
{
	EMythosFaction Best = EMythosFaction::CelestialOrder;
	int32 BestScore = GetFactionScore(Best);
	for (int32 i = 1; i < 6; ++i)
	{
		const EMythosFaction Faction = static_cast<EMythosFaction>(i);
		const int32 Score = GetFactionScore(Faction);
		if (Score > BestScore)
		{
			Best = Faction;
			BestScore = Score;
		}
	}
	return Best;
}

bool AMythosGameMode::IsFactionSpreadBalanced() const
{
	const TArray<int32> Scores = { Run.Celestial, Run.Aegis, Run.Dominion, Run.Undernet, Run.Abyssal, Run.FreeGrid };
	int32 MinScore = Scores[0];
	int32 MaxScore = Scores[0];
	for (int32 Score : Scores)
	{
		MinScore = FMath::Min(MinScore, Score);
		MaxScore = FMath::Max(MaxScore, Score);
	}
	return MaxScore - MinScore <= 3;
}

int32 AMythosGameMode::SuggestEndingIndex() const
{
	const int32 SteelKeys = Run.Inventory.FilterByPredicate([](const FString& Item) { return Item.StartsWith(TEXT("STEELKEY")); }).Num();
	const EMythosFaction Top = GetTopFaction();
	if (SteelKeys >= 2 && Run.NetPBond >= 7) return 5;
	if (IsFactionSpreadBalanced() && Run.Corruption >= 2 && Run.Corruption <= 4) return 4;
	if (Run.Corruption >= 7 || Top == EMythosFaction::AbyssalCovenant) return 3;
	if (Run.Z >= 1400 || Top == EMythosFaction::N3TDominion) return 2;
	if (Top == EMythosFaction::AegisConcord && Run.NetPBond <= 4) return 1;
	if (Top == EMythosFaction::CelestialOrder && Run.Corruption <= 3) return 0;
	return 4;
}

void AMythosGameMode::ApplyElementPerkAfterDay()
{
	if (Run.Element == EMythosElement::Aqua)
	{
		Run.HP = FMath::Clamp(Run.HP + 2, 0, Run.MaxHP);
	}
}

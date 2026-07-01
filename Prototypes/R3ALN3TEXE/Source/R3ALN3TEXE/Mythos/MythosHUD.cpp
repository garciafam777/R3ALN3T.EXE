#include "MythosHUD.h"

#include "CanvasItem.h"
#include "Engine/Canvas.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "MythosGameMode.h"

void AMythosHUD::DrawHUD()
{
	Super::DrawHUD();
	AMythosGameMode* GM = GetWorld()->GetAuthGameMode<AMythosGameMode>();
	if (!Canvas || !GM || !GEngine) return;

	FCanvasTileItem Bg(FVector2D(0.f, 0.f), FVector2D(Canvas->SizeX, Canvas->SizeY), FLinearColor(0.015f, 0.018f, 0.028f, 0.94f));
	Bg.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(Bg);

	DrawHeader(GM);
	switch (GM->Run.Screen)
	{
	case EMythosScreen::Start: DrawStart(GM); break;
	case EMythosScreen::CareerSelect: DrawCareerSelect(GM); break;
	case EMythosScreen::ElementSelect: DrawElementSelect(GM); break;
	case EMythosScreen::Work: DrawWork(GM); break;
	case EMythosScreen::StoryChoice: DrawStoryChoice(GM); break;
	case EMythosScreen::Battle: DrawBattle(GM); break;
	case EMythosScreen::Ending: DrawEnding(GM); break;
	case EMythosScreen::PostGame: DrawPostGame(GM); break;
	}
}

void AMythosHUD::DrawLineText(const FString& Text, float X, const FLinearColor& Color, float Scale)
{
	FCanvasTextItem Item(FVector2D(X, LineY), FText::FromString(Text), GEngine->GetSmallFont(), Color);
	Item.Scale = FVector2D(Scale, Scale);
	Item.EnableShadow(FLinearColor::Black);
	Canvas->DrawItem(Item);
	LineY += 20.f * Scale + 7.f;
}

void AMythosHUD::DrawHeader(AMythosGameMode* GM)
{
	LineY = 28.f;
	DrawLineText(TEXT("R3ALN3T.EXE // THE MYTHOS ORIGIN_3026"), 34.f, FLinearColor(0.1f, 1.f, 0.72f), 1.45f);
	DrawLineText(FString::Printf(TEXT("Day %d | Act %d | Rank %s | Career %s | Element %s | Objective: %s"),
		GM->Run.Day, GM->Run.ActIndex + 1, *GM->GetRankName(), *GM->GetCareerName(), *GM->GetElementName(), *GM->Run.Objective), 34.f, FLinearColor::White, 0.95f);
	DrawLineText(FString::Printf(TEXT("HP %d/%d | Z %d | Corruption %d | Astra Bond %d"),
		GM->Run.HP, GM->Run.MaxHP, GM->Run.Z, GM->Run.Corruption, GM->Run.NetPBond), 34.f, FLinearColor(1.f, 0.78f, 0.28f), 0.95f);
	DrawLineText(FString::Printf(TEXT("Factions: Celestial %d | Aegis %d | Dominion %d | Undernet %d | Abyssal %d | FreeGrid %d"),
		GM->Run.Celestial, GM->Run.Aegis, GM->Run.Dominion, GM->Run.Undernet, GM->Run.Abyssal, GM->Run.FreeGrid), 34.f, FLinearColor(0.7f, 0.8f, 1.f), 0.82f);
	LineY += 12.f;
}

void AMythosHUD::DrawStart(AMythosGameMode* GM)
{
	DrawLineText(TEXT("> MESSAGE FROM: MCADMIN"), 70.f, FLinearColor(0.1f, 1.f, 0.72f), 1.1f);
	DrawLineText(TEXT("> PRIORITY: ROOT"), 70.f, FLinearColor(0.1f, 1.f, 0.72f), 1.1f);
	DrawLineText(TEXT("> They are lying about the bugmatter. Find the Source."), 70.f, FLinearColor::White, 1.1f);
	DrawLineText(TEXT("> Your NetP knows more than you do. Do not let it hear you think."), 70.f, FLinearColor::White, 1.1f);
	LineY += 20.f;
	DrawLineText(TEXT("Press ENTER or 1 to wake up."), 70.f, FLinearColor(1.f, 0.78f, 0.28f), 1.2f);
}

void AMythosHUD::DrawCareerSelect(AMythosGameMode* GM)
{
	DrawLineText(TEXT("T3N3SS33 EMPLOYMENT TERMINAL"), 70.f, FLinearColor(1.f, 0.78f, 0.28f), 1.2f);
	for (int32 i = 0; i < GM->GetCareers().Num(); ++i)
	{
		const FMythosCareerData& Career = GM->GetCareers()[i];
		DrawLineText(FString::Printf(TEXT("%d. %s - %s | HP %d ATK %d TECH %d"),
			i + 1, *Career.Name, *Career.WorkSite, Career.MaxHP, Career.Attack, Career.Tech), 70.f, FLinearColor::White, 1.f);
	}
}

void AMythosHUD::DrawElementSelect(AMythosGameMode* GM)
{
	DrawLineText(TEXT("NAVI ELEMENT LINK"), 70.f, FLinearColor(1.f, 0.78f, 0.28f), 1.2f);
	static const TArray<FString> Perks = {
		TEXT("First-strike pressure: CrossStrike gets bonus damage."),
		TEXT("Aqua recovery: heal after each day."),
		TEXT("Terra guard: start battles with extra shield."),
		TEXT("Shade drift: Abyssal choices increase attack."),
		TEXT("Flare economy: shifts earn bonus Z."),
		TEXT("Signal empathy: choices add extra Navi bond.")
	};
	for (int32 i = 0; i < GM->GetElements().Num(); ++i)
	{
		DrawLineText(FString::Printf(TEXT("%d. %s - %s"), i + 1, *GM->GetElements()[i], *Perks[i]), 70.f, FLinearColor::White, 1.f);
	}
}

void AMythosHUD::DrawWork(AMythosGameMode* GM)
{
	const int32 CareerIndex = static_cast<int32>(GM->Run.Career);
	const FMythosCareerData& Career = GM->GetCareers()[CareerIndex];
	DrawLineText(FString::Printf(TEXT("%s SHIFT // %s"), *Career.Name, *Career.WorkSite), 70.f, FLinearColor(1.f, 0.78f, 0.28f), 1.2f);
	DrawLineText(TEXT("1 or SPACE: Run shift"), 70.f, FLinearColor::White, 1.f);
	DrawLineText(TEXT("2 or ENTER: Open the Day 3 lie once available"), 70.f, FLinearColor::White, 1.f);
	DrawLineText(FString::Printf(TEXT("Career lie: %s"), GM->Run.Day >= 3 ? *Career.Lie : TEXT("The system is still deciding how much truth you can carry.")), 70.f, FLinearColor(0.7f, 0.9f, 1.f), 1.f);
}

void AMythosHUD::DrawStoryChoice(AMythosGameMode* GM)
{
	const FMythosStoryNode& Node = GM->GetStoryNodes()[GM->ActiveStoryNode];
	DrawLineText(Node.Title, 70.f, FLinearColor(1.f, 0.78f, 0.28f), 1.2f);
	DrawLineText(Node.Body, 70.f, FLinearColor::White, 1.f);
	for (const FString& Line : Node.Terminal.ParseIntoArrayLines())
	{
		DrawLineText(Line, 90.f, FLinearColor(0.1f, 1.f, 0.72f), 0.95f);
	}
	LineY += 8.f;
	for (int32 i = 0; i < Node.Choices.Num(); ++i)
	{
		DrawLineText(FString::Printf(TEXT("%d. %s - %s"), i + 1, *Node.Choices[i].Label, *Node.Choices[i].Description), 70.f, FLinearColor::White, 0.95f);
	}
}

void AMythosHUD::DrawBattle(AMythosGameMode* GM)
{
	DrawLineText(FString::Printf(TEXT("N3T BATTLE: %s HP %d/%d | Shield %d"), *GM->BattleEnemyName, GM->BattleEnemyHP, GM->BattleEnemyMaxHP, GM->BattleShield), 70.f, FLinearColor(1.f, 0.32f, 0.44f), 1.2f);
	DrawLineText(TEXT("1 CrossStrike | 2 GuardWall | 3 DecodeHack | 4 PurifyBurst"), 70.f, FLinearColor::White, 1.f);
	DrawLineText(TEXT("[PLAYER 4x4] || [ENEMY 4x4]"), 70.f, FLinearColor(0.1f, 1.f, 0.72f), 1.f);
	for (int32 Row = 0; Row < 4; ++Row)
	{
		DrawLineText(TEXT("[ ][ ][N][ ] || [ ][X][ ][ ]"), 90.f, FLinearColor(0.7f, 0.9f, 1.f), 1.f);
	}
	LineY += 8.f;
	for (int32 i = 0; i < FMath::Min(6, GM->BattleLog.Num()); ++i)
	{
		DrawLineText(GM->BattleLog[i], 70.f, FLinearColor::White, 0.9f);
	}
}

void AMythosHUD::DrawEnding(AMythosGameMode* GM)
{
	DrawLineText(TEXT("ACT IV: MCADMIN RECKONING"), 70.f, FLinearColor(1.f, 0.78f, 0.28f), 1.2f);
	DrawLineText(TEXT("The final Source is inside your Navi code. Choose the world state."), 70.f, FLinearColor::White, 1.f);
	DrawLineText(FString::Printf(TEXT("SPACE: resolve by world state suggestion (%s)"), *GM->GetSuggestedEnding()), 70.f, FLinearColor(0.1f, 1.f, 0.72f), 1.f);
	DrawLineText(TEXT("1 Restoration | 2 Ascension | 3 Dominion | 4 Collapse | 5 Balance | 6 MCADMIN"), 70.f, FLinearColor::White, 1.f);
}

void AMythosHUD::DrawPostGame(AMythosGameMode* GM)
{
	DrawLineText(FString::Printf(TEXT("WORLD STATE: %s"), *GM->Run.EndingName), 70.f, FLinearColor(1.f, 0.78f, 0.28f), 1.2f);
	DrawLineText(TEXT("1 Run another day | 2 Descend one layer | 3 Shift rumor | R New run"), 70.f, FLinearColor::White, 1.f);
	LineY += 12.f;
	DrawLineText(TEXT("Inventory:"), 70.f, FLinearColor(0.1f, 1.f, 0.72f), 1.f);
	DrawLineText(FString::Join(GM->Run.Inventory, TEXT(", ")), 90.f, FLinearColor::White, 0.85f);
	LineY += 12.f;
	DrawLineText(TEXT("Recent Log:"), 70.f, FLinearColor(0.1f, 1.f, 0.72f), 1.f);
	for (const FString& Entry : GM->Run.Log)
	{
		DrawLineText(Entry, 90.f, FLinearColor::White, 0.82f);
	}
}

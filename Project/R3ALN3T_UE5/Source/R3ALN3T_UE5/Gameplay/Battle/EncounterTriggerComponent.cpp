#include "EncounterTriggerComponent.h"
#include "../../Gameplay/World/Public/WorldLayerManager.h"
#include "R3ALN3T_BattleManager.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

UEncounterTriggerComponent::UEncounterTriggerComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.TickGroup = TG_PrePhysics;

    // Default virus definitions
    CommonViruses = {
        {TEXT("VIRUS_MET"),     FText::FromString("Mettaur"),    20,  5,  0, 30, {TEXT("Cannon"), TEXT("AirShot")},    0.3f},
        {TEXT("VIRUS_FISH"),    FText::FromString("Fishy"),      15,  8,  0, 25, {TEXT("Bubble"), TEXT("Healing")},   0.25f},
        {TEXT("VIRUS_SWORD"),   FText::FromString("Swordy"),     25,  6,  2, 40, {TEXT("Sword"), TEXT("WideSword")},  0.2f},
        {TEXT("VIRUS_SHIELD"),  FText::FromString("Shieldy"),    30,  3,  5, 35, {TEXT("Guard"), TEXT("Barrier")},    0.15f},
    };
    Sector2Viruses = {
        {TEXT("VIRUS_SPIKEY"),  FText::FromString("Spikey"),     35, 10, 3,  50, {TEXT("Lance"), TEXT("Spear")},      0.25f},
        {TEXT("VIRUS_FLAME"),   FText::FromString("Flamey"),     28, 12, 1,  45, {TEXT("FireBurn"), TEXT("Heat")},    0.2f},
    };
    Sector3Viruses = {
        {TEXT("VIRUS_THUNDER"), FText::FromString("Thunder"),    40, 15, 4,  70, {TEXT("ElecPulse"), TEXT("Bolt")},   0.2f},
        {TEXT("VIRUS_DARK"),    FText::FromString("Shadow"),     50, 10, 8,  85, {TEXT("Darkness"), TEXT("Curse")},   0.15f},
    };
    BossViruses = {
        {TEXT("BOSS_POISON"),   FText::FromString("PoisonMist"), 100, 20, 10, 200, {TEXT("Poison"), TEXT("VirusChip")}, 0.5f},
        {TEXT("BOSS_OMEGA"),    FText::FromString("OmegaGuard"), 150, 25, 15, 300, {TEXT("OmegaChip"), TEXT("Giga")},  0.3f},
    };
}

void UEncounterTriggerComponent::BeginPlay()
{
    Super::BeginPlay();
    if (GetOwner())
    {
        LastLocation = GetOwner()->GetActorLocation();
        PlayerController = GetWorld()->GetFirstPlayerController();
    }
    // Find managers
    if (GetWorld())
    {
        // LayerManager and BattleManager would be fetched from GameInstance in full implementation
    }
}

void UEncounterTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!GetOwner() || !PlayerController) return;

    FVector CurrentLocation = GetOwner()->GetActorLocation();
    float DistanceMoved = FVector::Dist(CurrentLocation, LastLocation);

    if (DistanceMoved >= MinMoveThreshold)
    {
        TimeSinceLastStep = 0.0f;
        LastLocation = CurrentLocation;
        TryEncounter(CurrentLocation);
    }
}

void UEncounterTriggerComponent::TryEncounter(FVector CurrentLocation)
{
    // Check encounter chance based on zone
    float EncounterChance = 0.03f; // Base 3%

    // Roll
    if (FMath::FRand() <= EncounterChance)
    {
        TArray<FVirusDef> Viruses = PickVirusList(TEXT(""));
        if (Viruses.Num() == 0) return;

        int32 Count = FMath::RandRange(1, 3);
        TArray<FVirusDef> Encounter;
        for (int32 i = 0; i < Count; ++i)
        {
            int32 Idx = FMath::RandRange(0, Viruses.Num() - 1);
            Encounter.Add(Viruses[Idx]);
        }

        // Trigger battle (BattleManager would be called in full impl)
        UE_LOG(LogTemp, Log, TEXT("Random encounter! %d viruses ambushed the player."), Count);
    }
}

TArray<FVirusDef> UEncounterTriggerComponent::PickVirusList(const FString& ZoneTag)
{
    // Sector-based virus selection
    int32 Roll = FMath::RandRange(0, 100);
    if (Roll < 60) return CommonViruses;
    if (Roll < 80) return Sector2Viruses;
    if (Roll < 95) return Sector3Viruses;
    return BossViruses;
}

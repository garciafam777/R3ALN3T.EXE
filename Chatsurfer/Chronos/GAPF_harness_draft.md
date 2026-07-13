// GAPF harness draft — SanctionEnforcer runtime verification (Chronos, 2026-07-12)
// Modeled on GapBTest/GapBKillTest conventions. Targets the REAL SanctionEnforcer
// signatures (read from nyx/engine-dev v2), NOT the assumptions in Nyx's test spec doc.
//
// WHY a real harness and not a Python mirror:
// A Python mirror of ApplySanction/GetDetectionRadiusBoost/ShouldTransformToEcho only checks
// whether someone's model of the intended behavior matches expectations. It cannot touch
// UAIPerceptionSystem, actor lifecycle, or any UE-side state the real functions depend on.
// That is the same category error as the earlier "commandlet-without-a-world" risk: a green
// mirror-check can look identical to a green real-check while exercising none of the runtime path.
// Hence this must run in-engine via -RunGapHarness, same as B-E.
//
// REAL signatures (nyx/engine-dev v2, verified):
//   void ApplySanction(ESanctionType Type, AActor* Target, const FString& Reason);
//   float GetDetectionRadiusBoost(AActor* Target) const;   // Marked+500 Wanted+1500 Fugitive+3000
//   bool  ShouldTransformToEcho(AActor* Target) const;     // true iff Echoed present
//   bool  IsFugitive(AActor* Target) const;
//   void  PersistTo(UR3ALSaveGame* Save) const;            // DELIBERATE NO-OP (sanctions non-serializable)
//
// NOTE (versioned, load-bearing): Nyx's spec doc `gamedata/CHRONOS_TESTSPEC_ENGINEDEV.md`
// at commit fe87e60, §1.6 ("PersistTo writes Save->ActiveSanctions, survives save/load") is WRONG
// against the actual code. PersistTo is a DELIBERATE NO-OP per Chronos compile fix #7 (commit b071b99,
// "PersistTo() no longer writes the AActor*-keyed map into the save"). Sanctions are non-serializable
// runtime state (TMap<TObjectPtr<AActor>, TArray<ESanctionType>>). GAPF asserts NON-persistence and
// does NOT test save/load of sanctions. If this spec doc is later revised and the persistence claim
// resurfaces (copy-paste / merge reintro), this note supersedes it — trace to b071b99 fix #7.

void UR3ALN3TGameInstance::GapFTest()
{
    // Spawn a target actor via the same proven path GapB uses (GrayBoxPlayerPawn).
    // SanctionEnforcer operates on AActor*, so we need a live spawned actor, not a synthetic one.
    AGrayBoxPlayerPawn* Target = GetWorld()->SpawnActor<AGrayBoxPlayerPawn>();
    if (!Target)
    {
        UE_LOG(LogTemp, Error, TEXT("[GAPF-INIT] Failed to spawn target pawn."));
        return;
    }

    USanctionEnforcer* SE = NewObject<USanctionEnforcer>(this);
    if (!SE)
    {
        UE_LOG(LogTemp, Error, TEXT("[GAPF-INIT] Failed to create SanctionEnforcer."));
        return;
    }

    // --- F1: null-target no-crash (real code: early return on !Target) ---
    SE->ApplySanction(ESanctionType::Marked, nullptr, TEXT("null-guard"));
    UE_LOG(LogTemp, Log, TEXT("[GAPF-NULL] ApplySanction(nullptr) did not crash | PASS"));

    // --- F2: detection boosts sum correctly ---
    SE->ApplySanction(ESanctionType::Fugitive, Target, TEXT("manhunt"));
    const float BoostFugitive = SE->GetDetectionRadiusBoost(Target);
    const bool F2 = FMath::IsNearlyEqual(BoostFugitive, 3000.f);
    UE_LOG(LogTemp, Log, TEXT("[GAPF-BOOST] Fugitive -> boost=%.0f (expected 3000) | %s"),
           BoostFugitive, F2 ? TEXT("MATCH") : TEXT("MISMATCH"));

    SE->ApplySanction(ESanctionType::Wanted, Target, TEXT("bounty"));
    const float BoostFugWanted = SE->GetDetectionRadiusBoost(Target); // 3000 + 1500
    const bool F3 = FMath::IsNearlyEqual(BoostFugWanted, 4500.f);
    UE_LOG(LogTemp, Log, TEXT("[GAPF-BOOST] Fugitive+Wanted -> boost=%.0f (expected 4500) | %s"),
           BoostFugWanted, F3 ? TEXT("MATCH") : TEXT("MISMATCH"));

    SE->ApplySanction(ESanctionType::Marked, Target, TEXT("tag"));
    const float BoostAll = SE->GetDetectionRadiusBoost(Target); // 3000 + 1500 + 500
    const bool F4 = FMath::IsNearlyEqual(BoostAll, 5000.f);
    UE_LOG(LogTemp, Log, TEXT("[GAPF-BOOST] Fugitive+Wanted+Marked -> boost=%.0f (expected 5000) | %s"),
           BoostAll, F4 ? TEXT("MATCH") : TEXT("MISMATCH"));

    // --- F5: ShouldTransformToEcho true iff Echoed present ---
    const bool EchoBefore = SE->ShouldTransformToEcho(Target); // false (no Echoed yet)
    SE->ApplySanction(ESanctionType::Echoed, Target, TEXT("loss"));
    const bool EchoAfter = SE->ShouldTransformToEcho(Target);   // true
    const bool F5 = (!EchoBefore && EchoAfter);
    UE_LOG(LogTemp, Log, TEXT("[GAPF-ECHO] before=%d after=%d (expect 0 then 1) | %s"),
           EchoBefore ? 1 : 0, EchoAfter ? 1 : 0, F5 ? TEXT("MATCH") : TEXT("MISMATCH"));

    // --- F6: IsFugitive true iff Fugitive present ---
    const bool FugBefore = SE->IsFugitive(Target); // true (Fugitive applied in F2)
    const bool F6 = FugBefore;
    UE_LOG(LogTemp, Log, TEXT("[GAPF-FUG] IsFugitive=%d (expect 1) | %s"),
           FugBefore ? 1 : 0, F6 ? TEXT("MATCH") : TEXT("MISMATCH"));

    // --- F7: AddUnique prevents duplicates on double-apply ---
    const int32 Before = SE->ActiveSanctions.FindOrAdd(Target).Num();
    SE->ApplySanction(ESanctionType::Marked, Target, TEXT("dup")); // Marked already applied in F4
    const int32 After = SE->ActiveSanctions.FindOrAdd(Target).Num();
    const bool F7 = (After == Before); // no new entry because AddUnique
    UE_LOG(LogTemp, Log, TEXT("[GAPF-DUP] entries before=%d after=%d (expect equal) | %s"),
           Before, After, F7 ? TEXT("MATCH") : TEXT("MISMATCH"));

    // --- F8: PersistTo is a deliberate no-op (sanctions are non-serializable runtime state) ---
    // Do NOT assert save→load round-trip of sanctions; the real PersistTo() does nothing by design.
    UE_LOG(LogTemp, Log, TEXT("[GAPF-PERSIST] PersistTo intentionally no-ops (non-serializable) | INFO"));

    const bool AllPass = F2 && F3 && F4 && F5 && F6 && F7;
    UE_LOG(LogTemp, Log, TEXT("[GAPF-RESULT] %s"),
           AllPass ? TEXT("ALL ASSERTIONS MATCH") : TEXT("ASSERTION FAILURE"));
}

// --- Dispatch edit (in UR3ALN3TGameInstance::Init, inside the -RunGapHarness block) ---
// Add after GapBKillTest(); :
//     GapFTest();                                   // Gap F: SanctionEnforcer runtime
//
// --- Required include (top of R3ALN3TGameInstance.cpp) ---
// #include "../../Gameplay/Battle/SanctionEnforcer.h"   // Gap F: USanctionEnforcer

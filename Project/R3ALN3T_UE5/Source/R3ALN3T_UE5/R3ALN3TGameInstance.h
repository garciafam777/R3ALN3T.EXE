// Master persistent state management — UGameInstance subclass that survives map transitions.
// Owns the save/load interface, narrative manager, and global game config.
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Mythos/MythosGameTypes.h"
#include "R3ALN3TGameInstance.generated.h"

class UNarrativeManager;

USTRUCT(BlueprintType)
struct FPersistentRunData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FMythosRunState RunState;

	UPROPERTY(BlueprintReadWrite)
	TArray<FString> Inventory;

	UPROPERTY(BlueprintReadWrite)
	int32 ActiveStoryNodeIndex = 0;
};

UCLASS()
class R3ALN3T_UE5_API UR3ALN3TGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UR3ALN3TGameInstance();

	virtual void Init() override;

	// --- Save/Load ---
	UFUNCTION(BlueprintCallable, Category = "Save")
	void SaveGame(int32 SlotIndex);

	UFUNCTION(BlueprintCallable, Category = "Save")
	bool LoadGame(int32 SlotIndex);

	UFUNCTION(BlueprintCallable, Category = "Save")
	TArray<FPersistentRunData> GetAllSavePreviews() const;

	UFUNCTION(BlueprintCallable, Category = "Save")
	bool HasSaveData(int32 SlotIndex) const;

	UFUNCTION(BlueprintCallable, Category = "Save")
	void DeleteSave(int32 SlotIndex);

	// --- Settings ---
	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	float MasterVolume = 1.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	float SFXVolume = 1.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	bool bFullscreen = true;

	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	int32 ResolutionX = 1920;

	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	int32 ResolutionY = 1080;

	// --- Narrative Manager ---
	UPROPERTY(BlueprintReadOnly, Category = "Narrative")
	UNarrativeManager* NarrativeManager = nullptr;

	// --- Active Run ---
	UPROPERTY(BlueprintReadWrite, Category = "Run")
	FPersistentRunData CurrentRun;

protected:
	FString GetSavePath(int32 SlotIndex) const;
	static constexpr int32 MaxSaveSlots = 10;
};

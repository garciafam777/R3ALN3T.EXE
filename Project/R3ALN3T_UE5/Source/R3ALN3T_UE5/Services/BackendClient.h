// BackendClient.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Http.h"
#include "Json.h"
#include "Serialization/JsonSerializer.h"
#include "BackendClient.generated.h"

/**
 * REST Client for communicating with R3ALN3T backend
 * Handles all HTTP requests to Python FastAPI server
 */
UCLASS()
class R3ALN3T_UE5_API ABackendClient : public AActor
{
	GENERATED_BODY()

public:
	ABackendClient();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// ========================================================================
	// PLAYER ENDPOINTS
	// ========================================================================

	/**
	 * Create a new player character
	 * @param Username - Player's username
	 * @param Career - Career type (NetOp, Scientist, Soldier, etc.)
	 * @param Element - Primary element
	 */
	UFUNCTION(BlueprintCallable, Category = "Backend|Player")
	void CreatePlayer(const FString& Username, const FString& Career, const FString& Element);

	/**
	 * Get player data from backend
	 * @param PlayerId - Player's unique ID
	 */
	UFUNCTION(BlueprintCallable, Category = "Backend|Player")
	void GetPlayer(const FString& PlayerId);

	/**
	 * Update player data on backend
	 * @param PlayerData - JSON string of player data
	 */
	UFUNCTION(BlueprintCallable, Category = "Backend|Player")
	void UpdatePlayer(const FString& PlayerId, const FString& PlayerData);

	// ========================================================================
	// BATTLE ENDPOINTS
	// ========================================================================

	/**
	 * Start a new battle
	 * @param PlayerId - Player's ID
	 * @param EnemyNetPId - Enemy NetP construct ID
	 * @param ChipFolderId - Player's chip folder ID
	 */
	UFUNCTION(BlueprintCallable, Category = "Backend|Battle")
	void StartBattle(const FString& PlayerId, const FString& EnemyNetPId, const FString& ChipFolderId);

	/**
	 * Get current battle state
	 * @param BattleId - Battle's unique ID
	 */
	UFUNCTION(BlueprintCallable, Category = "Backend|Battle")
	void GetBattle(const FString& BattleId);

	/**
	 * Execute a battle turn (place chips on grid)
	 * @param BattleId - Battle's unique ID
	 * @param ChipPlacements - JSON array of chip placements
	 */
	UFUNCTION(BlueprintCallable, Category = "Backend|Battle")
	void ExecuteTurn(const FString& BattleId, const FString& ChipPlacements);

	/**
	 * End the current battle
	 * @param BattleId - Battle's unique ID
	 */
	UFUNCTION(BlueprintCallable, Category = "Backend|Battle")
	void EndBattle(const FString& BattleId);

	// ========================================================================
	// CHIP ENDPOINTS
	// ========================================================================

	/**
	 * Get all available chips (with optional filters)
	 * @param Element - Filter by element (optional)
	 * @param Rarity - Filter by rarity (optional)
	 */
	UFUNCTION(BlueprintCallable, Category = "Backend|Chips")
	void GetChips(const FString& Element = "", const FString& Rarity = "");

	/**
	 * Create a chip folder
	 * @param PlayerId - Player's ID
	 * @param FolderName - Name of the folder
	 */
	UFUNCTION(BlueprintCallable, Category = "Backend|Chips")
	void CreateFolder(const FString& PlayerId, const FString& FolderName);

	/**
	 * Add a chip to a folder
	 * @param FolderId - Folder's unique ID
	 * @param ChipId - Chip's unique ID
	 */
	UFUNCTION(BlueprintCallable, Category = "Backend|Chips")
	void AddChipToFolder(const FString& FolderId, const FString& ChipId);

	// ========================================================================
	// SAVE/LOAD ENDPOINTS
	// ========================================================================

	/**
	 * Save game state to backend
	 * @param PlayerId - Player's ID
	 * @param PlayerData - Serialized player state
	 * @param BattleData - Serialized active battle (optional)
	 */
	UFUNCTION(BlueprintCallable, Category = "Backend|Save")
	void SaveGame(const FString& PlayerId, const FString& PlayerData, const FString& BattleData = "");

	/**
	 * Load saved game from backend
	 * @param PlayerId - Player's ID to load
	 */
	UFUNCTION(BlueprintCallable, Category = "Backend|Save")
	void LoadGame(const FString& PlayerId);

	// ========================================================================
	// HEALTH & STATUS
	// ========================================================================

	/**
	 * Check backend health status
	 */
	UFUNCTION(BlueprintCallable, Category = "Backend|Health")
	void HealthCheck();

	// ========================================================================
	// DELEGATES & EVENTS
	// ========================================================================

	// Response delegates
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
		FOnPlayerCreated,
		bool, bSuccess,
		FString, PlayerId
	);
	UPROPERTY(BlueprintAssignable, Category = "Backend|Events")
	FOnPlayerCreated OnPlayerCreated;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
		FOnBattleStarted,
		bool, bSuccess,
		FString, BattleId
	);
	UPROPERTY(BlueprintAssignable, Category = "Backend|Events")
	FOnBattleStarted OnBattleStarted;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
		FOnTurnExecuted,
		bool, bSuccess,
		FString, PhaseLog
	);
	UPROPERTY(BlueprintAssignable, Category = "Backend|Events")
	FOnTurnExecuted OnTurnExecuted;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
		FOnGameSaved,
		bool, bSuccess,
		FString, SaveId
	);
	UPROPERTY(BlueprintAssignable, Category = "Backend|Events")
	FOnGameSaved OnGameSaved;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
		FOnDataReceived,
		bool, bSuccess,
		FString, JsonData
	);
	UPROPERTY(BlueprintAssignable, Category = "Backend|Events")
	FOnDataReceived OnDataReceived;

	// ========================================================================
	// CONFIGURATION
	// ========================================================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Backend|Config")
	bool bUseMockBackend = true;  // Area-2 fix: when true (default), skip live HTTP and
	                              // service requests from local UR3ALSaveGame. Prevents
	                              // null/standalone crashes when the FastAPI endpoint is down.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Backend|Config")
	FString BackendUrl = "http://127.0.0.1:8000";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Backend|Config")
	float RequestTimeout = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Backend|Config")
	bool bDebugLogging = true;

protected:
	// HTTP module reference
	FHttpModule* HttpModule;

	// Helper functions
	void MakeRequest(
		const FString& Endpoint,
		const FString& Verb,
		const FString& JsonContent,
		FSimpleDelegate OnSuccess,
		FSimpleDelegate OnFailure
	);

	void OnResponseReceived(
		FHttpRequestPtr Request,
		FHttpResponsePtr Response,
		bool bWasSuccessful
	);

	// Response handlers
	void OnCreatePlayerResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnGetPlayerResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnStartBattleResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnExecuteTurnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnSaveGameResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// Utility
	FString GetApiUrl(const FString& Endpoint) const;
	TSharedPtr<FJsonObject> ParseJsonResponse(const FString& JsonString) const;

	// Area-2 fix: local fallback when bUseMockBackend is true. Services the request from
	// UR3ALSaveGame (local disk) instead of the live FastAPI endpoint. Returns true if handled.
	bool HandleMockRequest(const FString& Endpoint, const FString& Verb, const FString& JsonContent);
	// Extracts the player_state sub-object as a JSON string for local stash.
	FString PlayerDataToNotes(const FString& JsonContent) const;

private:
	FString LastRequestType;
};

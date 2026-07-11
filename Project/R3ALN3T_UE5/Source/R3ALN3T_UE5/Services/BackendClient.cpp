// BackendClient.cpp
#include "BackendClient.h"
#include "Http.h"
#include "JsonUtilities.h"
#include "Kismet/GameplayStatics.h"

ABackendClient::ABackendClient()
{
	PrimaryActorTick.bCanEverTick = false;
	HttpModule = &FHttpModule::Get();
}

void ABackendClient::BeginPlay()
{
	Super::BeginPlay();

	if (bDebugLogging)
	{
		UE_LOG(LogTemp, Warning, TEXT("[BackendClient] Initialized - Backend: %s"), *BackendUrl);
	}
}

void ABackendClient::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// ============================================================================
// PLAYER ENDPOINTS
// ============================================================================

void ABackendClient::CreatePlayer(const FString& Username, const FString& Career, const FString& Element)
{
	FString Endpoint = "/api/v1/players/create";
	
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField("username", Username);
	JsonObject->SetStringField("career", Career);
	JsonObject->SetStringField("element", Element);

	FString JsonContent;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonContent);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

	LastRequestType = "CreatePlayer";

	MakeRequest(
		Endpoint,
		"POST",
		JsonContent,
		FSimpleDelegate(),
		FSimpleDelegate()
	);
}

void ABackendClient::GetPlayer(const FString& PlayerId)
{
	FString Endpoint = FString::Printf(TEXT("/api/v1/players/%s"), *PlayerId);
	LastRequestType = "GetPlayer";

	MakeRequest(
		Endpoint,
		"GET",
		"",
		FSimpleDelegate(),
		FSimpleDelegate()
	);
}

void ABackendClient::UpdatePlayer(const FString& PlayerId, const FString& PlayerData)
{
	FString Endpoint = FString::Printf(TEXT("/api/v1/players/%s"), *PlayerId);
	LastRequestType = "UpdatePlayer";

	MakeRequest(
		Endpoint,
		"PUT",
		PlayerData,
		FSimpleDelegate(),
		FSimpleDelegate()
	);
}

// ============================================================================
// BATTLE ENDPOINTS
// ============================================================================

void ABackendClient::StartBattle(const FString& PlayerId, const FString& EnemyNetPId, const FString& ChipFolderId)
{
	FString Endpoint = FString::Printf(
		TEXT("/api/v1/battles/start?player_id=%s&enemy_netp_id=%s&chip_folder_id=%s"),
		*PlayerId, *EnemyNetPId, *ChipFolderId
	);

	LastRequestType = "StartBattle";

	MakeRequest(
		Endpoint,
		"POST",
		"",
		FSimpleDelegate(),
		FSimpleDelegate()
	);
}

void ABackendClient::GetBattle(const FString& BattleId)
{
	FString Endpoint = FString::Printf(TEXT("/api/v1/battles/%s"), *BattleId);
	LastRequestType = "GetBattle";

	MakeRequest(
		Endpoint,
		"GET",
		"",
		FSimpleDelegate(),
		FSimpleDelegate()
	);
}

void ABackendClient::ExecuteTurn(const FString& BattleId, const FString& ChipPlacements)
{
	FString Endpoint = FString::Printf(TEXT("/api/v1/battles/%s/execute-turn"), *BattleId);

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField("chip_placements", ChipPlacements);

	FString JsonContent;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonContent);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

	LastRequestType = "ExecuteTurn";

	MakeRequest(
		Endpoint,
		"POST",
		JsonContent,
		FSimpleDelegate(),
		FSimpleDelegate()
	);
}

void ABackendClient::EndBattle(const FString& BattleId)
{
	FString Endpoint = FString::Printf(TEXT("/api/v1/battles/%s/end"), *BattleId);
	LastRequestType = "EndBattle";

	MakeRequest(
		Endpoint,
		"POST",
		"",
		FSimpleDelegate(),
		FSimpleDelegate()
	);
}

// ============================================================================
// CHIP ENDPOINTS
// ============================================================================

void ABackendClient::GetChips(const FString& Element, const FString& Rarity)
{
	FString Endpoint = "/api/v1/chips";
	
	if (!Element.IsEmpty() || !Rarity.IsEmpty())
	{
		Endpoint += "?";
		if (!Element.IsEmpty())
		{
			Endpoint += FString::Printf(TEXT("element=%s"), *Element);
		}
		if (!Rarity.IsEmpty())
		{
			Endpoint += FString::Printf(TEXT("&rarity=%s"), *Rarity);
		}
	}

	LastRequestType = "GetChips";

	MakeRequest(
		Endpoint,
		"GET",
		"",
		FSimpleDelegate(),
		FSimpleDelegate()
	);
}

void ABackendClient::CreateFolder(const FString& PlayerId, const FString& FolderName)
{
	FString Endpoint = FString::Printf(
		TEXT("/api/v1/folders/create?player_id=%s&name=%s"),
		*PlayerId, *FolderName
	);

	LastRequestType = "CreateFolder";

	MakeRequest(
		Endpoint,
		"POST",
		"",
		FSimpleDelegate(),
		FSimpleDelegate()
	);
}

void ABackendClient::AddChipToFolder(const FString& FolderId, const FString& ChipId)
{
	FString Endpoint = FString::Printf(
		TEXT("/api/v1/folders/%s/add-chip?chip_id=%s"),
		*FolderId, *ChipId
	);

	LastRequestType = "AddChipToFolder";

	MakeRequest(
		Endpoint,
		"PUT",
		"",
		FSimpleDelegate(),
		FSimpleDelegate()
	);
}

// ============================================================================
// SAVE/LOAD ENDPOINTS
// ============================================================================

void ABackendClient::SaveGame(const FString& PlayerId, const FString& PlayerData, const FString& BattleData)
{
	FString Endpoint = "/api/v1/save";

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(FStringView(TEXT("player_id")), PlayerId);
	JsonObject->SetStringField(FStringView(TEXT("player_state")), PlayerData);
	
	if (!BattleData.IsEmpty())
	{
		JsonObject->SetStringField(FStringView(TEXT("active_battle")), BattleData);
	}

	FString JsonContent;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonContent);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

	LastRequestType = "SaveGame";

	MakeRequest(
		Endpoint,
		"POST",
		JsonContent,
		FSimpleDelegate(),
		FSimpleDelegate()
	);
}

void ABackendClient::LoadGame(const FString& PlayerId)
{
	FString Endpoint = FString::Printf(TEXT("/api/v1/load/%s"), *PlayerId);
	LastRequestType = "LoadGame";

	MakeRequest(
		Endpoint,
		"GET",
		"",
		FSimpleDelegate(),
		FSimpleDelegate()
	);
}

// ============================================================================
// HEALTH & STATUS
// ============================================================================

void ABackendClient::HealthCheck()
{
	FString Endpoint = "/health";
	LastRequestType = "HealthCheck";

	MakeRequest(
		Endpoint,
		"GET",
		"",
		FSimpleDelegate(),
		FSimpleDelegate()
	);
}

// ============================================================================
// HELPER FUNCTIONS
// ============================================================================

void ABackendClient::MakeRequest(
	const FString& Endpoint,
	const FString& Verb,
	const FString& JsonContent,
	FSimpleDelegate OnSuccess,
	FSimpleDelegate OnFailure
)
{
	if (!HttpModule)
	{
		UE_LOG(LogTemp, Error, TEXT("[BackendClient] HTTP module not available"));
		return;
	}

	FHttpRequestRef Request = HttpModule->CreateRequest();
	Request->SetURL(GetApiUrl(Endpoint));
	Request->SetVerb(Verb);
	Request->SetHeader("Content-Type", "application/json");
	Request->SetHeader("User-Agent", "R3ALN3T-Client/1.0");

	if (!JsonContent.IsEmpty())
	{
		Request->SetContentAsString(JsonContent);
	}

	// Bind response handler
	Request->OnProcessRequestComplete().BindUObject(this, &ABackendClient::OnResponseReceived);

	if (bDebugLogging)
	{
		UE_LOG(LogTemp, Warning, TEXT("[BackendClient] %s Request: %s %s"), *LastRequestType, *Verb, *Endpoint);
	}

	Request->ProcessRequest();
}

void ABackendClient::OnResponseReceived(
	FHttpRequestPtr Request,
	FHttpResponsePtr Response,
	bool bWasSuccessful
)
{
	if (!bWasSuccessful || !Response.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("[BackendClient] Request failed: %s"), *LastRequestType);
		OnDataReceived.Broadcast(false, "Request failed");
		return;
	}

	int32 ResponseCode = Response->GetResponseCode();
	FString ResponseContent = Response->GetContentAsString();

	if (bDebugLogging)
	{
		UE_LOG(LogTemp, Warning, TEXT("[BackendClient] Response: %d - %s"), ResponseCode, *ResponseContent);
	}

	// Handle different response types
	if (LastRequestType == "CreatePlayer")
	{
		OnCreatePlayerResponse(Request, Response, bWasSuccessful);
	}
	else if (LastRequestType == "GetPlayer")
	{
		OnGetPlayerResponse(Request, Response, bWasSuccessful);
	}
	else if (LastRequestType == "StartBattle")
	{
		OnStartBattleResponse(Request, Response, bWasSuccessful);
	}
	else if (LastRequestType == "ExecuteTurn")
	{
		OnExecuteTurnResponse(Request, Response, bWasSuccessful);
	}
	else if (LastRequestType == "SaveGame")
	{
		OnSaveGameResponse(Request, Response, bWasSuccessful);
	}
	else
	{
		// Generic response
		OnDataReceived.Broadcast(ResponseCode == 200, ResponseContent);
	}
}

void ABackendClient::OnCreatePlayerResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful && Response.IsValid())
	{
		TSharedPtr<FJsonObject> JsonObject = ParseJsonResponse(Response->GetContentAsString());
		if (JsonObject.IsValid())
		{
			TSharedPtr<FJsonObject> PlayerObj = JsonObject->GetObjectField(TEXT("player"));
			FString PlayerId = PlayerObj.IsValid() ? PlayerObj->GetStringField(TEXT("id")) : TEXT("");
			OnPlayerCreated.Broadcast(true, PlayerId);
			return;
		}
	}

	OnPlayerCreated.Broadcast(false, "");
}

void ABackendClient::OnGetPlayerResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful && Response.IsValid())
	{
		OnDataReceived.Broadcast(true, Response->GetContentAsString());
		return;
	}

	OnDataReceived.Broadcast(false, "");
}

void ABackendClient::OnStartBattleResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful && Response.IsValid())
	{
		TSharedPtr<FJsonObject> JsonObject = ParseJsonResponse(Response->GetContentAsString());
		if (JsonObject.IsValid())
		{
			TSharedPtr<FJsonObject> BattleObj = JsonObject->GetObjectField(TEXT("battle_state"));
			FString BattleId = BattleObj.IsValid() ? BattleObj->GetStringField(TEXT("id")) : TEXT("");
			OnBattleStarted.Broadcast(true, BattleId);
			return;
		}
	}

	OnBattleStarted.Broadcast(false, "");
}

void ABackendClient::OnExecuteTurnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful && Response.IsValid())
	{
		OnTurnExecuted.Broadcast(true, Response->GetContentAsString());
		return;
	}

	OnTurnExecuted.Broadcast(false, "");
}

void ABackendClient::OnSaveGameResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful && Response.IsValid())
	{
		TSharedPtr<FJsonObject> JsonObject = ParseJsonResponse(Response->GetContentAsString());
		if (JsonObject.IsValid())
		{
			FString SaveId = JsonObject->GetStringField(TEXT("save_id"));
			OnGameSaved.Broadcast(true, SaveId);
			return;
		}
	}

	OnGameSaved.Broadcast(false, "");
}

FString ABackendClient::GetApiUrl(const FString& Endpoint) const
{
	return BackendUrl + Endpoint;
}

TSharedPtr<FJsonObject> ABackendClient::ParseJsonResponse(const FString& JsonString) const
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
	
	if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
	{
		return JsonObject;
	}

	return nullptr;
}

#include "R3ALN3T_PositionTracker.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

UR3ALN3T_PositionTracker::UR3ALN3T_PositionTracker()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = TG_PrePhysics;
}

void UR3ALN3T_PositionTracker::BeginPlay()
{
	Super::BeginPlay();
	TimeSinceLastReport = 0.0f;
}

void UR3ALN3T_PositionTracker::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TimeSinceLastReport += DeltaTime;
	if (TimeSinceLastReport >= ReportInterval)
	{
		TimeSinceLastReport = 0.0f;
		ReportPositionNow();
	}
}

void UR3ALN3T_PositionTracker::ReportPositionNow()
{
	if (!GetOwner()) return;

	FPositionPayload Payload;
	Payload.EntityID = EntityID;
	Payload.Location = GetOwner()->GetActorLocation();
	Payload.CurrentLayer = CurrentLayer;
	Payload.Timestamp = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;

	OnPositionReported.Broadcast(Payload);
	SendPositionAsync(Payload);
}

void UR3ALN3T_PositionTracker::SendPositionAsync(const FPositionPayload& Payload)
{
	TSharedPtr<FJsonObject> Json = MakeShareable(new FJsonObject());
	Json->SetStringField(TEXT("entity_id"), Payload.EntityID);
	Json->SetNumberField(TEXT("x"), Payload.Location.X);
	Json->SetNumberField(TEXT("y"), Payload.Location.Y);
	Json->SetNumberField(TEXT("z"), Payload.Location.Z);
	Json->SetNumberField(TEXT("layer"), static_cast<int32>(Payload.CurrentLayer));
	Json->SetNumberField(TEXT("timestamp"), Payload.Timestamp);

	FString OutputString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(Json.ToSharedRef(), Writer);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(TelemetryEndpoint);
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetContentAsString(OutputString);
	Request->OnProcessRequestComplete().BindLambda([](
		FHttpRequestPtr Req, FHttpResponsePtr Resp, bool bSuccess)
	{
		if (bSuccess && Resp.IsValid())
		{
			UE_LOG(LogTemp, Verbose, TEXT("PositionTracker: %d %s"), Resp->GetResponseCode(), *Resp->GetContentAsString());
		}
	});
	Request->ProcessRequest();
}

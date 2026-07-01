// Asynchronous spatial tracker — fires JSON position payloads to local telemetry backend
// on a background thread so the game thread is never blocked.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Data/R3ALN3T_WorldStructures.h"
#include "R3ALN3T_PositionTracker.generated.h"

USTRUCT(BlueprintType)
struct FPositionPayload
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString EntityID;

	UPROPERTY(BlueprintReadWrite)
	FVector Location = FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite)
	ER3ALN3TLayer CurrentLayer = ER3ALN3TLayer::Reality;

	UPROPERTY(BlueprintReadWrite)
	float Timestamp = 0.0f;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPositionReported, FPositionPayload, Payload);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class R3ALN3T_UE5_API UR3ALN3T_PositionTracker : public UActorComponent
{
	GENERATED_BODY()

public:
	UR3ALN3T_PositionTracker();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Telemetry")
	FString EntityID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Telemetry")
	FString TelemetryEndpoint = TEXT("http://127.0.0.1:8080/api/position");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Telemetry")
	float ReportInterval = 1.0f; // seconds between reports

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Telemetry")
	ER3ALN3TLayer CurrentLayer = ER3ALN3TLayer::Reality;

	UPROPERTY(BlueprintAssignable)
	FOnPositionReported OnPositionReported;

	UFUNCTION(BlueprintCallable, Category = "Telemetry")
	void ReportPositionNow();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float TimeSinceLastReport = 0.0f;
	void SendPositionAsync(const FPositionPayload& Payload);
};

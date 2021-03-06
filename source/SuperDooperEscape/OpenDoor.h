// Bryan Pritchett 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUPERDOOPERESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
	void OpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	void CloseDoor();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(VisibleAnywhere)
		float OpenAngle = 90.0f;
	UPROPERTY(EditAnywhere)
		ATriggerVolume*	PressurePlate;
	UPROPERTY(VisibleAnywhere)
	AActor* ActorThatOpens;
	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 1.0f;

	float LastDoorOpenTime;
	bool IsDoorOpen = false;

};

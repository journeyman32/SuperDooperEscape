// Bryan Pritchett 2019


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UOpenDoor::OpenDoor()
{
	AActor* Owner = GetOwner();
	const FRotator NewRotation = FRotator(0.0f, 90.0f, 0.0f);
	Owner->SetActorRotation(NewRotation);
	
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	ActorThatOpens =GetWorld()->GetFirstPlayerController()->GetPawn();
	
}

void UOpenDoor::CloseDoor()
{
	AActor* Owner = GetOwner();
	const FRotator NewRotation = FRotator(0.0f, -90.0f, 0.0f);
	Owner->SetActorRotation(NewRotation);
	IsDoorOpen = false;
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(PressurePlate ->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
		UE_LOG(LogClass, Log, TEXT("Door Opened At: %f"), LastDoorOpenTime);
		IsDoorOpen = true;
		//UE_LOG(LogClass, Log, TEXT("Door is: %s"), IsDoorOpen);
	}

	if(IsDoorOpen)
	{
		float CloseTime = LastDoorOpenTime + DoorCloseDelay;
		UE_LOG(LogClass, Log, TEXT("Door close time: %f"), CloseTime);
		if(GetWorld()->GetTimeSeconds() >= CloseTime)
		{
			UE_LOG(LogClass, Log, TEXT("Going to close door"));
			CloseDoor();
		}
	}
}


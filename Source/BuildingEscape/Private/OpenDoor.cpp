// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"





// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	AActor* ownerPtr = GetOwner();
	
	FRotator rotator = ownerPtr->GetActorRotation();
	FRotator newRotation = FRotator(rotator.Pitch, rotator.Yaw - 60.f, rotator.Roll);

	//Set the door rotation
	ownerPtr->SetActorRotation(newRotation);


	UE_LOG(LogTemp, Warning, TEXT("Rotator: %s"), *rotator.ToString());

	// ...
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


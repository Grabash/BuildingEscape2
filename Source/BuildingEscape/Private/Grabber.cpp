// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#define OUT


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	playerController_ptr = GetWorld()->GetFirstPlayerController();

	FString pwnName;
	pwnName = GetOwner()->GetName();

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!/nGrabber attached to: %s"), *pwnName )

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get player view point this tick
	FVector playerViewPointLocation;
	FRotator playerViewPointRotation;

	playerController_ptr->GetPlayerViewPoint(
		OUT playerViewPointLocation,
		OUT playerViewPointRotation);

	// UE_LOG(LogTemp, Warning,TEXT("ViewPoint location: %s \n ViewPoint direction: %s"), *playerViewPointLocation.ToString(), *playerViewPointRotation.ToString())

	// FVector lineTraceEnd = playerViewPointLocation + FVector(0.f, 0.f, 50.f);
	FVector lineTraceEnd = playerViewPointLocation + playerViewPointRotation.Vector() * reach;

	DrawDebugLine(GetWorld(), playerViewPointLocation, lineTraceEnd,
			FColor(255, 0, 0),
			false,
			0.0f,
			0.f,
			10.0f);


	// Ray-cast out to reach distance

	// See what we hit

	// ...
}


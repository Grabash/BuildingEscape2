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

	//playerController_ptr = GetWorld()->GetFirstPlayerController();

	//FString pwnName;
	//pwnName = GetOwner()->GetName();

	//UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!\nGrabber attached to: %s"), *pwnName)

	findPhysicsHandleComponent();
	setupInputComponent();




	// ...
	
}

void UGrabber::setupInputComponent()
{
	inputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (inputComponent) {
		FString objectName = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("InputComponent attached to %s!"), *objectName)

			/// Bind the input axis
			inputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		inputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}



// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/////////////////////////////

	APlayerController* playerController_ptr = GetWorld()->GetFirstPlayerController();
	FVector playerViewPointLocation;
	FRotator playerViewPointRotation;

	playerController_ptr->GetPlayerViewPoint(
		OUT playerViewPointLocation,
		OUT playerViewPointRotation);

	// UE_LOG(LogTemp, Warning,TEXT("ViewPoint location: %s \n ViewPoint direction: %s"), *playerViewPointLocation.ToString(), *playerViewPointRotation.ToString())

	// FVector lineTraceEnd = playerViewPointLocation + FVector(0.f, 0.f, 50.f);
	FVector lineTraceEnd = playerViewPointLocation + playerViewPointRotation.Vector() * reach;

	/////////////////////////////////


	// if physics handle is attached
	if (PhysicsHandle->GrabbedComponent)
	{
		// move the object that we're holding
		PhysicsHandle->SetTargetLocation(lineTraceEnd);


	}
		

	

	 



	// ...
}

void UGrabber::Grab()
{
	
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed!"))


		// Try and reach any actors with physics body collision channel set
		auto hitResult = getFirstPhysicsBodyInReach();
	auto componentToGrab = hitResult.GetComponent();
	auto actorHit = hitResult.GetActor();
	
	/// if we hit something then attach a physics handle
	if (actorHit) {
		// TODO attach physics handle
		PhysicsHandle->GrabComponent(componentToGrab, NAME_None,
			componentToGrab->GetOwner()->GetActorLocation(),
			true); // allow rotation

	}
	

}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab key released!"))
		// TODO release physics handle
		PhysicsHandle->ReleaseComponent();
}

FHitResult UGrabber::getFirstPhysicsBodyInReach() const
{
	// Get player view point this tick
	APlayerController* playerController_ptr = GetWorld()->GetFirstPlayerController();
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


	// Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	// Ray-cast out to reach distance

	FHitResult hit;

	GetWorld()->LineTraceSingleByObjectType(
		OUT hit,
		playerViewPointLocation,
		lineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters);
	/// See what we hit

	AActor* objectHit = hit.GetActor();
	FString objectHitName;

	if (objectHit)
	{
		objectHitName = objectHit->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Actor hit: %s"), *objectHitName)
	}



	return hit;
}


void UGrabber::findPhysicsHandleComponent()
{
	/// Look for attached PhysicsHandle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) {
		/// Physics handle is found
	}
	else {
		FString objectName = GetOwner()->GetName();
		UE_LOG(LogTemp, Error, TEXT("No PhysicsHandle component found on %s object! Please add PhysicsHandle."), *objectName)
	}
}


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "OpenDoor.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{

	GENERATED_BODY()


private:
	AActor* ownerPtr = nullptr;
	FRotator rotator;

	UPROPERTY(EditAnywhere)
	float openAngle = 60.0f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	//UPROPERTY(EditAnywhere)
	// AActor* actorThatOpens;

	UPROPERTY(EditAnywhere)
		float doorCloseDelay = 1.f;

	UPROPERTY(EditAnywhere)
		float requiredMass = 0.f;

	float lastDoorOpenTime;


public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float GetTotalMassOfActorsOnPlate();

		
	
};


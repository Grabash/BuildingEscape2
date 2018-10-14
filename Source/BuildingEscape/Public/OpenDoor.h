// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "OpenDoor.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{

	GENERATED_BODY()


private:
	AActor* ownerPtr = nullptr;
	FRotator rotator;

	/*UPROPERTY(EditAnywhere)
	float openAngle = 60.0f;*/

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	//UPROPERTY(EditAnywhere)
	// AActor* actorThatOpens;

	/*UPROPERTY(EditAnywhere)
		float doorCloseDelay = 1.f;*/

	//Mass on PressurePlate required for the door to open.
	UPROPERTY(EditAnywhere)
		float requiredMass = 0.f;

	

	// float lastDoorOpenTime;


public:	
	// Sets default values for this component's properties
	UOpenDoor();
	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnOpen;

	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnClose;



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	
	/** OpenAngle property declared in C++ made available in Blueprint */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = OpenAngleCPP)
		float OpenAngleCPP = 0.f;
	

	// void OpenDoor();
	// void CloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float GetTotalMassOfActorsOnPlate();

		
	
};


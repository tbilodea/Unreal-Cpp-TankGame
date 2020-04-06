// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public/Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerTankController.generated.h"

/**
 * 
 */
UCLASS()
class TANKGAME_API APlayerTankController : public APlayerController
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere)
    float CrossHairXLocation= 0.5f;

	UPROPERTY(EditAnywhere)
    float CrossHairYLocation = 0.3333f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 10000.0f;

	ATank* GetControlledTank() const;

	//Start the tank moving the barrel toward crosshair vector
	void AimTowardCrosshair();
	bool GetSightRayHitLocation(FVector& HitLocation);
	bool GetLookVectorHitLocation(FVector WorldDirection, FVector& HitLocation) const;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};

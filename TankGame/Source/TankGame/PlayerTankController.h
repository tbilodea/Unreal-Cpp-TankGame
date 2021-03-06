// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerTankController.generated.h"

class UTankAimingComponent;

/**
 * All player controlled pawn's settings
 */
UCLASS()
class TANKGAME_API APlayerTankController : public APlayerController
{
	GENERATED_BODY()
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:
	UTankAimingComponent* AimingComponent = nullptr;

	UPROPERTY(EditAnywhere)
    float CrossHairXLocation= 0.5f;

	UPROPERTY(EditAnywhere)
    float CrossHairYLocation = 0.3333f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.0f;

	//Start the tank moving the barrel toward crosshair vector
	void AimTowardCrosshair();
	bool GetSightRayHitLocation(FVector& HitLocation);
	bool GetLookVectorHitLocation(FVector WorldDirection, FVector& HitLocation) const;
	
	UFUNCTION()
	void OnTankDeath();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetPawn(APawn* InPawn) override;

};

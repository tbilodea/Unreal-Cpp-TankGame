// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankBarrel;
class UTurret;
class AProjectile;

UCLASS()
class TANKGAME_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);
	
	UFUNCTION(BlueprintCallable, Category = Input)
	void Fire();

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 4000.f;

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	//Reference for spawning projectile
	UTankBarrel* Barrel = nullptr;

	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

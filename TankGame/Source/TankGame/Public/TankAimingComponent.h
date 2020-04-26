// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked,
	NoAmmo
};

class AProjectile;
class UTankBarrel;
class UTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKGAME_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTurret* TurretToSet, TSubclassOf<AProjectile> ProjectileBPToSet);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Fire();

	void AimAt(FVector HitLocation);

	EFiringStatus GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "Input")
	int GetRoundsLeft();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

private:
	UTankBarrel* Barrel = nullptr;
	UTurret* Turret = nullptr;
	TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;

	float LastFireTime = 0.f;
	FVector AimDirection = FVector(0);
	int AmmoCount = 5;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000.f;

	UPROPERTY(EditDefaultsOnly)
	float BarrelMoveSpeed = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3.f;

	void MoveBarrel();
	bool IsBarrelMoving();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Turret.h"
#include "Components/StaticMeshComponent.h" 
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTurret* TurretToSet)
{
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if(!Barrel){ return; }
	if(!Turret){ return; }

	FVector TossVelocity = FVector(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

    UE_LOG(LogTemp, Warning, TEXT("Hit location is %s and start loc is %s"), *HitLocation.ToString(), *StartLocation.ToString());
	bool HasAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this, 
		TossVelocity, 
		StartLocation,
		HitLocation, 
		LaunchSpeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace
		);

	if(HasAimSolution)
	{
		auto AimDirection = TossVelocity.GetSafeNormal();
    	UE_LOG(LogTemp, Warning, TEXT("has aim solution"));

		MoveBarrel(AimDirection);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NO aim solution"));
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}


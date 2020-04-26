// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Turret.h"
#include "Projectile.h"
#include "Components/StaticMeshComponent.h" 
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTurret* TurretToSet, TSubclassOf<AProjectile> ProjectileToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
	ProjectileBlueprint = ProjectileToSet;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = GetWorld()->GetTimeSeconds();

	if(!ensure(Barrel)) { return; }
	AimDirection = Barrel->GetForwardVector();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if(AmmoCount <= 0)
	{
		FiringStatus = EFiringStatus::NoAmmo;
	}
	else if( (GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringStatus = EFiringStatus::Reloading;
	}
	else if(IsBarrelMoving())
	{
		FiringStatus = EFiringStatus::Aiming;
	}
	else
	{
		FiringStatus = EFiringStatus::Locked;
	}
}

EFiringStatus UTankAimingComponent::GetFiringState() const
{
	return FiringStatus;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if(!ensure(Barrel)) { return false; }

	FVector BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01f);
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if(!ensure(Barrel && Turret)){ return; }

	FVector TossVelocity = FVector(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

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
		AimDirection = TossVelocity.GetSafeNormal();
		MoveBarrel();
	}
}

void UTankAimingComponent::MoveBarrel()
{
	if(!Barrel || !Turret) { return; }

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	if(FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
}

void UTankAimingComponent::Fire()
{
	if(FiringStatus == EFiringStatus::Reloading || FiringStatus == EFiringStatus::NoAmmo){ return; }

	LastFireTime = GetWorld()->GetTimeSeconds();
	
	if(!ensure(Barrel)) {return; }
	if(!ensure(ProjectileBlueprint)) {return; }

	//Spawn projectile at barrel socket Projectile location
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBlueprint, 
		Barrel->GetSocketLocation(FName("Projectile")),
		Barrel->GetSocketRotation(FName("Projectile")));

	Projectile->LaunchProjectile(LaunchSpeed);

	AmmoCount--;
}

int UTankAimingComponent::GetRoundsLeft()
{
	return AmmoCount;
}
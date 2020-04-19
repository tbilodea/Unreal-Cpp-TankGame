// Copyright Bilodeau 2020

#include "PlayerTankController.h"
#include "Public/TankAimingComponent.h"
#include "Camera/PlayerCameraManager.h" 
#include "Engine/World.h"
#include "Public/Tank.h"

void APlayerTankController::BeginPlay()
{
    Super::BeginPlay();

    auto AimComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();

    if(ensure(AimComponent)) {
        FoundAimingComponent(AimComponent);
    }
}

ATank* APlayerTankController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void APlayerTankController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    AimTowardCrosshair();
}

void APlayerTankController::AimTowardCrosshair()
{
    auto ControlledTank = GetControlledTank();
    if(!ensure(ControlledTank)) { return; }

    FVector HitLocation;

    if(GetSightRayHitLocation(HitLocation))
    {
        //Move barrel towards aiming at point
        ControlledTank->AimAt(HitLocation);
    }
}

bool APlayerTankController::GetSightRayHitLocation(FVector& HitLocation)
{
    //Find Crosshair position
    //"De project" to world direction
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);

    auto ScreenLocation = FVector2D(ViewportSizeX*CrossHairXLocation, ViewportSizeY*CrossHairYLocation);
    
    FVector WorldDirection, WorldLocation;
    DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, WorldDirection);
        
    if(GetLookVectorHitLocation(WorldDirection, HitLocation))
    {
        return true;
    }
    return false;
}

bool APlayerTankController::GetLookVectorHitLocation(FVector WorldDirection, FVector& HitLocation) const
{
    //Line trace to see what is hit
    FHitResult Hit;
    auto CameraLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = LineTraceRange * WorldDirection + CameraLocation;

    if(GetWorld()->LineTraceSingleByChannel(Hit, CameraLocation, 
        EndLocation, ECollisionChannel::ECC_Visibility))
    {
        HitLocation = Hit.Location;
        return true;
    }
    HitLocation = FVector(0);

    return false;
}

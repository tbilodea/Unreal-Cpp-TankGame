// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerTankController.h"
#include "Camera/PlayerCameraManager.h" 
#include "Engine/World.h"

void APlayerTankController::BeginPlay()
{
    Super::BeginPlay();

    auto PlayerTank = GetControlledTank();
    if(!PlayerTank){
        UE_LOG(LogTemp, Error, TEXT("PlayerTankController did not find a Tank Pawn"));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("PlayerTankController found tank pawn: %s"), *PlayerTank->GetName());
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
    if(!GetControlledTank()) { return; }

    FVector HitLocation;

    if(GetSightRayHitLocation(HitLocation))
    {
        //Move barrel towards aiming at point
        GetControlledTank()->AimAt(HitLocation);
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

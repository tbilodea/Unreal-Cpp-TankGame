// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

//Handles the elevation of the barrel
void UTankBarrel::Elevate(float RelativeSpeed)
{
    auto ElevationChange = FMath::Clamp(RelativeSpeed, -1.f, 1.f) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
    
    //Clamping to max/min elevation
    auto NewElevation = FMath::Clamp(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
    SetRelativeRotation(FRotator(NewElevation, 0, 0));
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

void UTurret::Rotate(float RelativeDirection)
{
    auto RotateChange = FMath::Clamp(RelativeDirection, -1.f, 1.f) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto NewRotation = RelativeRotation.Yaw + RotateChange;
    SetRelativeRotation(FRotator(0, NewRotation, 0));
}
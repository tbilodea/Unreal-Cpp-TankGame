// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTracks.h"

void UTankTracks::SetThrottle(float Throttle)
{
    float ClampedThrottle = FMath::Clamp(Throttle, -1.f, +1.f);

    auto ForceApplied = GetForwardVector() * ClampedThrottle * MaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}


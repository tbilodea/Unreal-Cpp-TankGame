// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTracks.h"

UTankTracks::UTankTracks()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTankTracks::SetThrottle(float Throttle)
{
    CurrentThrottle = FMath::Clamp(CurrentThrottle + Throttle, -1.f, +1.f);
}

void UTankTracks::BeginPlay()
{
    Super::BeginPlay();

    OnComponentHit.AddDynamic(this, &UTankTracks::OnHit);
}

void UTankTracks::AddDrivingForce()
{
    auto ForceApplied = GetForwardVector() * CurrentThrottle * MaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTracks::ApplySidewaysForce()
{
    //Calculate slippage speed
    float SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
    //Work out required acceleration to correct
    auto DeltaTime = GetWorld()->GetDeltaSeconds();
    auto CorrectionAcceleration = - SlippageSpeed / DeltaTime * GetRightVector();
    //Calc apply sideways force to fix
    auto TankRoot = Cast<UStaticMeshComponent>(GetOwner() -> GetRootComponent());
    auto CorrectionForce = TankRoot -> GetMass() * CorrectionAcceleration /2;
    TankRoot -> AddForce(CorrectionForce);
}

void UTankTracks::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    AddDrivingForce();
    ApplySidewaysForce();
    CurrentThrottle = 0;
}
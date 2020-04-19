// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTracks.h"

void UTankMovementComponent::Initialize(UTankTracks* LeftTrackToSet, UTankTracks* RightTrackToSet)
{
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
    if(!LeftTrack || !RightTrack) { return; }

    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendRotateClockwise(float Throw)
{
    if(!LeftTrack || !RightTrack) { return; }

    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
    //Virtual call, no need for super
    auto TankForward = GetOwner()->GetActorForwardVector();
    auto AIForwardIntention = MoveVelocity.GetSafeNormal();

    float ForwardThrow = FVector::DotProduct(AIForwardIntention, TankForward);
    FVector Cross = FVector::CrossProduct(TankForward, AIForwardIntention);

    IntendMoveForward(ForwardThrow);
    IntendRotateClockwise(Cross.Z);
}


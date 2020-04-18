// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTracks.h"

void UTankMovementComponent::Initialize(UTankTracks* LeftTrackToSet, UTankTracks* RightTrackToSet)
{
    if(!LeftTrackToSet || !RightTrackToSet){ return; }

    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
    if(!LeftTrack || !RightTrack) { return; }

    UE_LOG(LogTemp, Warning, TEXT("Intend move forward: %f"), Throw);
    
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
}


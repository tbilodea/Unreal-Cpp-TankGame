// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

    AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

    if(!ensure(PlayerTank && AimingComponent)) { return; }
    
    MoveToActor(PlayerTank, AcceptanceRadius);

    //Aim
    AimingComponent->AimAt(PlayerTank->GetActorLocation());

    //Fire
    if(AimingComponent->GetFiringState() == EFiringStatus::Locked)
    {
        AimingComponent->Fire();
    }

}
// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    auto ThisTank = Cast<ATank>(GetPawn());
    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

    if(PlayerTank)
    {
        //Aim
        ThisTank->AimAt(PlayerTank->GetActorLocation());

        //Fire
        ThisTank->Fire();
    }
}
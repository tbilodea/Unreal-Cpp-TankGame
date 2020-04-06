// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

    auto ControlledTank = GetControlledTank();
    if (!ControlledTank)
    {
        UE_LOG(LogTemp, Error, TEXT("TankAIController did not find a Tank pawn"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("TankAIController found a Tank pawn: %s"), *ControlledTank->GetName());
    }
}

ATank *ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

ATank *ATankAIController::GetPlayerController() const
{
    auto Player = GetWorld()->GetFirstPlayerController()->GetPawn();
    if (!Player)
    {
        return nullptr;
    }
    return Cast<ATank>(Player);
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    auto ThisTank = GetControlledTank();
    auto PlayerTank = GetPlayerController();

    if(PlayerTank)
    {
        //Aim
        ThisTank->AimAt(PlayerTank->GetActorLocation());

        //Fire
    }
}
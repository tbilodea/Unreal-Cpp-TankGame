// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();


    auto ControlledTank = GetControlledTank();
    if(!ControlledTank)
    {
        UE_LOG(LogTemp, Error, TEXT("TankAIController did not find a Tank pawn"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("TankAIController found a Tank pawn: %s"), *ControlledTank->GetName());
    }
}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}
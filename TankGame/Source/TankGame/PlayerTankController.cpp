// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTankController.h"

void APlayerTankController::BeginPlay()
{
    Super::BeginPlay();

    auto PlayerTank = GetControlledTank();
    if(!PlayerTank){
        UE_LOG(LogTemp, Warning, TEXT("PlayerTankController did not find a Tank Pawn"));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("PlayerTankController found tank pawn: %s"), *PlayerTank->GetName());
    }
}

ATank* APlayerTankController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

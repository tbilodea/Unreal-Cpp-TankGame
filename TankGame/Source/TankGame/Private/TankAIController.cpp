// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

    AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    auto PlayerController = GetWorld()->GetFirstPlayerController();

    if(!ensure(PlayerController && AimingComponent)) { return; }
    
    auto PlayerTank = PlayerController->GetPawn();

    if(!ensure(PlayerTank)) { return; }

    MoveToActor(PlayerTank, AcceptanceRadius);

    //Aim
    AimingComponent->AimAt(PlayerTank->GetActorLocation());

    //Fire
    if(AimingComponent->GetFiringState() == EFiringStatus::Locked)
    {
        AimingComponent->Fire();
    }

}

void ATankAIController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);

    if(InPawn)
    {
        auto PossessedTank = Cast<ATank>(InPawn);
        if(!ensure(PossessedTank)) { return;}

        //Sub tank's death
        PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
    }
}

void ATankAIController::OnTankDeath()
{
    auto ControlledPawn = GetPawn();
    if(!ensure(ControlledPawn)) { return; }
    ControlledPawn->DetachFromControllerPendingDestroy();
}


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class TANKGAME_API ATank : public APawn
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercentage();

	FTankDelegate OnDeath;

private:
	UPROPERTY(EditDefaultsOnly)
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere)
	int32 CurrentHealth; //init in beginplay

	// Sets default values for this pawn's properties
	ATank();

	virtual void BeginPlay() override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

};

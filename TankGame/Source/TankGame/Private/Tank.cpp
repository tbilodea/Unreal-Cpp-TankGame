// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

float ATank::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, 
	AController* EventInstigator, AActor* DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(Damage);
	int32 ClampDamage = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= ClampDamage;
	if(CurrentHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("DEAD"));
	}

	UE_LOG(LogTemp, Warning, TEXT("Damage amt %f damage to apply %i"), Damage, ClampDamage);
	return ClampDamage;
}

float ATank::GetHealthPercentage()
{
	return (float)CurrentHealth/(float)StartingHealth;
}
// Copyright Bilodeau 2020


#include "Mortar.h"

// Sets default values
AMortar::AMortar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

float AMortar::GetHealthPercentage()
{
	return (float)CurrentHealth/(float)StartingHealth;
}

float AMortar::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	int32 IntDamage = FPlatformMath::RoundToInt(Damage);
	int32 ClampedDamage = FMath::Clamp(IntDamage, 0, CurrentHealth);

	CurrentHealth -= ClampedDamage;

	return ClampedDamage;
}
// Copyright Bilodeau 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Mortar.generated.h"

UCLASS()
class TANKGAME_API AMortar : public APawn
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercentage();
	
private:
	UPROPERTY(EditDefaultsOnly)
	int32 StartingHealth = 40;

	UPROPERTY(VisibleAnywhere)
	int32 CurrentHealth = StartingHealth;

	// Sets default values for this pawn's properties
	AMortar();

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

};

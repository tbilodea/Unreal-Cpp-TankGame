// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKGAME_API UTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Rotate(float RelativeDirection);

private:
	UPROPERTY(EditDefaultsOnly)
	float MaxDegreesPerSecond = 10.f;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float DegreesPerSecond)
{
    UE_LOG(LogTemp, Warning, TEXT("TankBarrel moving by %f degrees per second"), DegreesPerSecond);
}
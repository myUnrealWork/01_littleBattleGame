// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories = (""))
class BATTLEGAME_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	

public:
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditAnyWhere, Category = Setup)
		float MaxDegreesPerSecond = 10;
	UPROPERTY(EditAnyWhere, Category = Setup)
		float MaxElevationDegrees = 30; // TODO set
	UPROPERTY(EditAnyWhere, Category = Setup)
		float MinElevationDegrees = 0; // TODO set
};

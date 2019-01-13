// Individual Game.

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
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxDegreesPerSecond = 10;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxElevationDegrees = 30; // TODO set
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MinElevationDegrees = 0; // TODO set
};

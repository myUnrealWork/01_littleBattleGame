// Individual Game.

#include "TankTurret.h"


void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond *GetWorld()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Yaw + ElevationChange;
	SetRelativeRotation(FRotator(0, Rotation, 0));
}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;
/**
 * Responsible for driving the tank tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLEGAME_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public://被蓝图使用需为public
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankTrack *LeftTrackToSet, UTankTrack *RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendMoveForward(float Throw); // control throw

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendTurnRight(float Throw);

	// TODO check best protection of this method
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

private:
	UTankTrack *LeftTrack = nullptr;
	UTankTrack *RightTrack = nullptr;
};

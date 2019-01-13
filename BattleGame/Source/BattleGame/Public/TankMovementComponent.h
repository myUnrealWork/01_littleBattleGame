// Individual Game.

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
	// 初始化左右轮胎
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankTrack *LeftTrackToSet, UTankTrack *RightTrackToSet);
	//驱动向前移动
	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendMoveForward(float Throw); // control throw
	//驱动右转----
	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendTurnRight(float Throw);

	
private:
	// Called from the pathfinding logic by AI controllers
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	UTankTrack *LeftTrack = nullptr;
	UTankTrack *RightTrack = nullptr;
};

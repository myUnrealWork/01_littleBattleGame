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

public://����ͼʹ����Ϊpublic
	// ��ʼ��������̥
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankTrack *LeftTrackToSet, UTankTrack *RightTrackToSet);
	//������ǰ�ƶ�
	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendMoveForward(float Throw); // control throw
	//������ת----
	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendTurnRight(float Throw);

	
private:
	// Called from the pathfinding logic by AI controllers
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	UTankTrack *LeftTrack = nullptr;
	UTankTrack *RightTrack = nullptr;
};

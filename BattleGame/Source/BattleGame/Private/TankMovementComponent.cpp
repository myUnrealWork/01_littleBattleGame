// Individual Game.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack *LeftTrackToSet, UTankTrack *RightTrackToSet)
{
	if (!ensure(LeftTrackToSet)||!ensure(RightTrackToSet)) { return; } //原本此行为 ！xx|| ！xx
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack) || !ensure(RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	UE_LOG(LogTemp, Warning, TEXT("move:%f"),Throw); 

	//TODO prevent double-speed due to dual control use
}

//即将左转和右转的力 选择性地右转力的方向
void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(LeftTrack) || !ensure(RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
	UE_LOG(LogTemp, Warning, TEXT("turn :%f"), Throw);
	//TODO prevent double-speed due to dual control use
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call Super as we're replacing the functionality
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal(); //局部坐标的x朝向的向量
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();// AI寻路下一个方向朝向的向量
	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);//余弦cos两向量 
	IntendMoveForward(ForwardThrow);
	
	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;//正弦 sin 世界坐标下比较转向
	IntendTurnRight(RightThrow);
}


// Individual Game.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack *LeftTrackToSet, UTankTrack *RightTrackToSet)
{
	if (!ensure(LeftTrackToSet)||!ensure(RightTrackToSet)) { return; } //ԭ������Ϊ ��xx|| ��xx
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

//������ת����ת���� ѡ���Ե���ת���ķ���
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
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal(); //�ֲ������x���������
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();// AIѰ·��һ�������������
	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);//����cos������ 
	IntendMoveForward(ForwardThrow);
	
	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;//���� sin ���������±Ƚ�ת��
	IntendTurnRight(RightThrow);
}


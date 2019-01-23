// Individual Game.

#include "TankTrack.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	// Drive the tracks
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0;// ������ֵ //ע�ʹ��п����ƶ��� ��Ҫ����ǰ������input��������
}

void UTankTrack::ApplySidewaysForce()
{
	// Calculate the slippage speed, sideways component speed
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	// work-out the required acceleration this frame to correct
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = SlippageSpeed / DeltaTime * GetRightVector() * -1;
	// calculate and apply sideways for (F= ma)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());// �ҵ����
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; //two tracks
	TankRoot->AddForce(CorrectionForce);

	////#########################################################################################################
	////---------------------------------------------------------------------------------------------------------
	//auto RootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());// �ҵ����
	//auto TankVelocity = RootComponent->GetComponentVelocity();//�ҵ����ڵ��ƶ��ٶ�
	//auto RightVector = RootComponent->GetRightVector();//�ҵ��ƶ�����
	////�ҵ��໬ �ٶȣ�
	//auto SideSpeed = FVector::DotProduct(RightVector, TankVelocity);//������˻�������floatֵ
	//
	////�ҵ��໬���Ӧ�ļ��ٶ�
	//float DeltaTime = GetWorld()->GetDeltaSeconds();
	//auto SideSpeedAcceleration = SideSpeed / DeltaTime * GetRightVector()*-1;// ͨ��RightVector ��-1ֵ�������󣨷����򣩵���

	////F=ma
	//auto CorrectForce = (RootComponent->GetMass()*SideSpeedAcceleration) / 2; // half of force per track  //һ���Ĵ�һ��CorrectForce(��Left��Right��Tank��)
	//RootComponent->AddForce(CorrectForce);
	////----------------------------------------------------------------------------------------------------------
	////##########################################################################################################
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	// USceneComponent ���� ת ���� UPrimitiveComponent // USceneComponent ���������FVector���Ͳ���
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
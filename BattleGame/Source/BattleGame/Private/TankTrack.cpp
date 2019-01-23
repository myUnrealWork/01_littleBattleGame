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
	CurrentThrottle = 0;// 重置阈值 //注释此行可以移动； 需要调整前后左右input后再启用
}

void UTankTrack::ApplySidewaysForce()
{
	// Calculate the slippage speed, sideways component speed
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	// work-out the required acceleration this frame to correct
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = SlippageSpeed / DeltaTime * GetRightVector() * -1;
	// calculate and apply sideways for (F= ma)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());// 找到组件
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; //two tracks
	TankRoot->AddForce(CorrectionForce);

	////#########################################################################################################
	////---------------------------------------------------------------------------------------------------------
	//auto RootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());// 找到组件
	//auto TankVelocity = RootComponent->GetComponentVelocity();//找到现在的移动速度
	//auto RightVector = RootComponent->GetRightVector();//找到移动方向
	////找到侧滑 速度，
	//auto SideSpeed = FVector::DotProduct(RightVector, TankVelocity);//向量点乘积，返回float值
	//
	////找到侧滑相对应的加速度
	//float DeltaTime = GetWorld()->GetDeltaSeconds();
	//auto SideSpeedAcceleration = SideSpeed / DeltaTime * GetRightVector()*-1;// 通过RightVector 的-1值来加向左（反方向）的力

	////F=ma
	//auto CorrectForce = (RootComponent->GetMass()*SideSpeedAcceleration) / 2; // half of force per track  //一个履带一个CorrectForce(有Left和Right在Tank上)
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
	// USceneComponent 类型 转 子类 UPrimitiveComponent // USceneComponent 不允许被添加FVector类型参数
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
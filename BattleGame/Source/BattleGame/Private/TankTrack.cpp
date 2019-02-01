// Individual Game.

#include "TankTrack.h"

#include "SprungWheel.h"
#include "SpawnPonit.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

//void UTankTrack::BeginPlay()
//{
//	Super::BeginPlay();
//	//OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
//}

//void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
//{
//	// Drive the tracks
//	// DriveTrack(); // 使用wheels 后将不再在此处使用
//	ApplySidewaysForce();
//	/*CurrentThrottle = 0;*/// 重置阈值 //注释此行可以移动； 需要调整前后左右input后再启用
//}

//void UTankTrack::ApplySidewaysForce()
//{
//	// Calculate the slippage speed, sideways component speed
//	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
//	// work-out the required acceleration this frame to correct
//	auto DeltaTime = GetWorld()->GetDeltaSeconds();
//	auto CorrectionAcceleration = SlippageSpeed / DeltaTime * GetRightVector() * -1;
//	// calculate and apply sideways for (F= ma)
//	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());// 找到组件
//	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; //two tracks
//	TankRoot->AddForce(CorrectionForce);
//
//	////#########################################################################################################
//	////---------------------------------------------------------------------------------------------------------
//	//auto RootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());// 找到组件
//	//auto TankVelocity = RootComponent->GetComponentVelocity();//找到现在的移动速度
//	//auto RightVector = RootComponent->GetRightVector();//找到移动方向
//	////找到侧滑 速度，
//	//auto SideSpeed = FVector::DotProduct(RightVector, TankVelocity);//向量点乘积，返回float值
//	//
//	////找到侧滑相对应的加速度
//	//float DeltaTime = GetWorld()->GetDeltaSeconds();
//	//auto SideSpeedAcceleration = SideSpeed / DeltaTime * GetRightVector()*-1;// 通过RightVector 的-1值来加向左（反方向）的力
//
//	////F=ma
//	//auto CorrectForce = (RootComponent->GetMass()*SideSpeedAcceleration) / 2; // half of force per track  //一个履带一个CorrectForce(有Left和Right在Tank上)
//	//RootComponent->AddForce(CorrectForce);
//	////----------------------------------------------------------------------------------------------------------
//	////##########################################################################################################
//}

void UTankTrack::SetThrottle(float Throttle)
{
	//CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);// 弃用的：因为不再有滑动，因此没有残余的throttle，只需要进行限制即可
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	// --旧版本添加Force移动--
	//auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	//auto ForceLocation = GetComponentLocation();
	//// USceneComponent 类型 转 子类 UPrimitiveComponent // USceneComponent 不允许被添加FVector类型参数
	//auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	//TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

	auto ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
	auto Wheels = GetWheels(); //获取到Tarray中每个Sprungwheel的指针
	auto ForcePerWheel = ForceApplied / Wheels.Num();
	for (ASprungWheel* Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> ResultArray;
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);
	for (USceneComponent* Child : Children)
	{
		// cast USceneComp to USpawnPoint 
		auto SpawnPointChild = Cast<USpawnPonit>(Child);
		if (!SpawnPointChild) continue;

		// 获取 生成的 SpawnPoint actor
		AActor* SpawnedChild = SpawnPointChild->GetSpawnedActor();

		// cast SpawnPoint AActor to SprungWheel
		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
		if (!SprungWheel) continue;

		// 添加到结果集
		ResultArray.Add(SprungWheel);
	}
	return ResultArray;
}

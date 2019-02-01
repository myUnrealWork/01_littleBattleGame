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
//	// DriveTrack(); // ʹ��wheels �󽫲����ڴ˴�ʹ��
//	ApplySidewaysForce();
//	/*CurrentThrottle = 0;*/// ������ֵ //ע�ʹ��п����ƶ��� ��Ҫ����ǰ������input��������
//}

//void UTankTrack::ApplySidewaysForce()
//{
//	// Calculate the slippage speed, sideways component speed
//	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
//	// work-out the required acceleration this frame to correct
//	auto DeltaTime = GetWorld()->GetDeltaSeconds();
//	auto CorrectionAcceleration = SlippageSpeed / DeltaTime * GetRightVector() * -1;
//	// calculate and apply sideways for (F= ma)
//	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());// �ҵ����
//	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; //two tracks
//	TankRoot->AddForce(CorrectionForce);
//
//	////#########################################################################################################
//	////---------------------------------------------------------------------------------------------------------
//	//auto RootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());// �ҵ����
//	//auto TankVelocity = RootComponent->GetComponentVelocity();//�ҵ����ڵ��ƶ��ٶ�
//	//auto RightVector = RootComponent->GetRightVector();//�ҵ��ƶ�����
//	////�ҵ��໬ �ٶȣ�
//	//auto SideSpeed = FVector::DotProduct(RightVector, TankVelocity);//������˻�������floatֵ
//	//
//	////�ҵ��໬���Ӧ�ļ��ٶ�
//	//float DeltaTime = GetWorld()->GetDeltaSeconds();
//	//auto SideSpeedAcceleration = SideSpeed / DeltaTime * GetRightVector()*-1;// ͨ��RightVector ��-1ֵ�������󣨷����򣩵���
//
//	////F=ma
//	//auto CorrectForce = (RootComponent->GetMass()*SideSpeedAcceleration) / 2; // half of force per track  //һ���Ĵ�һ��CorrectForce(��Left��Right��Tank��)
//	//RootComponent->AddForce(CorrectForce);
//	////----------------------------------------------------------------------------------------------------------
//	////##########################################################################################################
//}

void UTankTrack::SetThrottle(float Throttle)
{
	//CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);// ���õģ���Ϊ�����л��������û�в����throttle��ֻ��Ҫ�������Ƽ���
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	// --�ɰ汾���Force�ƶ�--
	//auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	//auto ForceLocation = GetComponentLocation();
	//// USceneComponent ���� ת ���� UPrimitiveComponent // USceneComponent ���������FVector���Ͳ���
	//auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	//TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

	auto ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
	auto Wheels = GetWheels(); //��ȡ��Tarray��ÿ��Sprungwheel��ָ��
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

		// ��ȡ ���ɵ� SpawnPoint actor
		AActor* SpawnedChild = SpawnPointChild->GetSpawnedActor();

		// cast SpawnPoint AActor to SprungWheel
		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
		if (!SprungWheel) continue;

		// ��ӵ������
		ResultArray.Add(SprungWheel);
	}
	return ResultArray;
}

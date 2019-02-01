// Individual Game.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Engine//World.h"
#include "Tank.h"

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}
}

void ATankPlayerController::OnPossessedTankDeath()
{
	StartSpectatingOnly();
}

//��ʼ
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!GetPawn()) return;
	//��һ����c++������������ ���ң�������ͼ��ʵ��
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensureAlways(AimingComponent)) { return; }

	FoundAimingComponent(AimingComponent);

	//if (!ControlledTank)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("PlayController not possessing a tank."));
	//}
	//else 
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("PlayController possessing a tank: %s "), *(ControlledTank->GetName()));
	//}
}

//ÿ֡ 
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}



//��׼׼��
void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; } // e.g. if not possessing
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensureAlways(AimingComponent)) { return; }

	FVector HitLocation; //Out parameter
	if (GetSightRayHitLocation(HitLocation)) // Has "side-effect",is going to line trace 
	{
		AimingComponent->AimAt(HitLocation);
		// Tell controlled tank to aim at this point
	}
}

//����������ײλ��
//Get world location if linetrace through crosshair. true if hit landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairyLocation);
	
	//de-project... the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		//Line-trace along that LookDirection, and see what we hit (up to max range)
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);

		/*UE_LOG(LogTemp, Warning, TEXT("Location: %s "), *LookDirection.ToString());*/
	}
	return false;
}

//��2D��Ļ����λ��ת��Ϊ����ռ�3D����ͷ��� �����ز���ֵ
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const
{
	FVector CamerWorldLocation; // To be discarded

	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CamerWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const
{
	FHitResult HitResult; //��ײ�����

	//��ʼ�� ��ʼλ�á��յ�λ��
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation+(LookDirection * LineTraceRange);

	//��ʼ����������ײ���
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult, //�����
		StartLocation, //��ʼλ��
		EndLocation, //�յ�λ��
		ECollisionChannel::ECC_Camera) //����ײͨ�� �� ѡ���������ײ��� 
		)
	{
		// ���Ϊtrue��������� ��ײλ��  ��¼ ����ֵ��HitLocation
		HitLocation = HitResult.Location;
		return true;
	}
	//���Ϊfalse��������ײ���λ��Ϊ0��0��0 
	HitLocation = FVector(0);
	return false; //Line trace didn't succeed 
}

//��ȡ����̹��
//ATank* ATankPlayerController::GetControlledTank() const
//{
//	return Cast<ATank>(GetPawn());
//}



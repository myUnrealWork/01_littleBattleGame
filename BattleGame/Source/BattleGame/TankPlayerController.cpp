// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "GameFramework/Actor.h"
#include "Engine//World.h"

//��ʼ
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayController not possessing a tank."));
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayController possessing a tank: %s "), *(ControlledTank->GetName()));
	}
}

//ÿ֡ 
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

//��ȡ����̹��
ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

//��׼׼��
void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
	FVector HitLocation; //Out parameter
	if (GetSightRayHitLocation(HitLocation)) // Has "side-effect",is going to line trace 
	{
		GetControlledTank()->AimAt(HitLocation);
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
		GetLookVectorHitLocation(LookDirection, OutHitLocation);

		/*UE_LOG(LogTemp, Warning, TEXT("Location: %s "), *LookDirection.ToString());*/
	}
	return true;
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
		ECollisionChannel::ECC_Visibility) //����ײͨ�� �� ѡ���������ײ��� 
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




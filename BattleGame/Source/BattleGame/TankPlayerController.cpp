// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "GameFramework/Actor.h"
#include "Engine//World.h"

//开始
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

//每帧 
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

//获取控制坦克
ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

//瞄准准心
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

//视线射线碰撞位置
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

//将2D屏幕坐标位置转化为世界空间3D坐标和方向 并返回布尔值
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const
{
	FVector CamerWorldLocation; // To be discarded

	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CamerWorldLocation, LookDirection);
}


bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const
{
	FHitResult HitResult; //碰撞结果集

	//初始化 起始位置、终点位置
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation+(LookDirection * LineTraceRange);

	//开始进行射线碰撞检测
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult, //结果集
		StartLocation, //起始位置
		EndLocation, //终点位置
		ECollisionChannel::ECC_Visibility) //在碰撞通道 中 选择可视性碰撞检测 
		)
	{
		// 检测为true，将结果集 碰撞位置  记录 并赋值给HitLocation
		HitLocation = HitResult.Location;
		return true;
	}
	//检测为false，设置碰撞检测位置为0，0，0 
	HitLocation = FVector(0);
	return false; //Line trace didn't succeed 
}




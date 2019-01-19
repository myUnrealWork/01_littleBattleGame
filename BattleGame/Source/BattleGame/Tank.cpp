// Individual Game.

#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	////在构建时不太不需要使用指针保护
	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	//去掉下面一行，将MoveComponent设置为可自由添加的蓝图组件
	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
}

//// Called when the game starts or when spawned
//void ATank::BeginPlay()
//{
//	Super::BeginPlay();
//	//TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
//}

////蓝图组件
//void ATank::AimAt(FVector HitLocation)
//{
//	if (!ensureAlways(TankAimingComponent)) { return; }
//	TankAimingComponent->AimAt(HitLocation,LaunchSpeed);
//}

//void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
//{
//	TankAimingComponent->SetBarrelReference(BarrelToSet);
//	Barrel = BarrelToSet;
//}
//
//void ATank::SetTurretReference(UTankTurret* TurretToSet)
//{
//	TankAimingComponent->SetTurretReference(TurretToSet);
//}

//// Called to bind functionality to input
//void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}
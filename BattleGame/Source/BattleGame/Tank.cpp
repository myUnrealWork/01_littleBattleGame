// Individual Game.

#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	////�ڹ���ʱ��̫����Ҫʹ��ָ�뱣��
	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	//ȥ������һ�У���MoveComponent����Ϊ��������ӵ���ͼ���
	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
}

//// Called when the game starts or when spawned
//void ATank::BeginPlay()
//{
//	Super::BeginPlay();
//	//TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
//}

////��ͼ���
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
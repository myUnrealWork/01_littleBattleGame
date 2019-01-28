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

void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);
	//UE_LOG(LogTemp, Warning, TEXT("DamageAmount=%f , DamageToApply=%i "), DamageAmount, DamageToApply);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
	}
	

	return DamageToApply;
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
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



// Individual Game.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Enum for aiming state
UENUM()
enum class EFiringState :uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};

class UTankBarrel; // Forward declaration
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLEGAME_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	bool IsBarrelMoving();

	void AimAt(FVector HitLocation);

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

	EFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = Firing)
	int GetRoundsLeft() const;

	//void SetBarrelReference(UTankBarrel *BarrelToSet);
	//void SetTurretReference(UTankTurret *TurretToSet);

protected://asking to access these property from a subclass

	UPROPERTY(BlueprintReadOnly, Category = Setup)
	EFiringState FiringState = EFiringState::Reloading;

private:
	// method

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) override;

	void MoveBarrelTowards(FVector AimDirection);

	// 变量
	UTankBarrel *Barrel = nullptr;
	UTankTurret *Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;
	//UClass *ProjectileBlueprint; // 可以使用此语句 在蓝图中配置 Projectile_BP

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3;
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000; // Sensible starting value of 40 m/s

	double LastFireTime = 0;

	FVector AimDirection;

	int RoundsLeft = 3;//剩余弹药
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward declaration
class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;

UCLASS()
class BATTLEGAME_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//引用组件
	UTankAimingComponent *TankAimingComponent = nullptr;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelReference(UTankBarrel *BarrelToSet);
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretReference(UTankTurret *TurretToSet);
	UPROPERTY(EditAnyWhere, Category = Firing)
		float LaunchSpeed = 4000; // Sensible starting value of 40 m/s
	UFUNCTION(BlueprintCallable, Category = Setup)
		void Fire();


};

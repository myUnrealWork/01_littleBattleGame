// Individual Game.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class UPhysicsConstraintComponent;
class USphereComponent; 

UCLASS()
class BATTLEGAME_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float ForceMagnitude);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetupConstraint();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void ApplyForce();

	// Component section
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	USphereComponent*  Wheel = nullptr;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	USphereComponent*  Axle = nullptr;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UPhysicsConstraintComponent* MassWheelConstraint = nullptr;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UPhysicsConstraintComponent* AxleWheelConstraint = nullptr;

	float TotalForceMagnitudeThisFrame = 0;

private:

	
};

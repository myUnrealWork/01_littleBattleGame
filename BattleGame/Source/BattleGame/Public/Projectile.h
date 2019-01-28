// Individual Game.

#pragma once

class UParticleSystemComponent;
class URadialForceComponent;

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLEGAME_API AProjectile : public AActor
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AProjectile();

	void LaunchProjectile(float Speed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit);

	void OnTimerExpire();

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float DestoryDelay = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float ProjectileDamage = 20.f;

	UProjectileMovementComponent *ProjectileMovement = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent*  CollisionMesh = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UParticleSystemComponent* LaunchBlast = nullptr;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UParticleSystemComponent* ImpactBlast = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	URadialForceComponent* ExplosionForce = nullptr;
};

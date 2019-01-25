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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit);

public:	
	// Sets default values for this actor's properties
	AProjectile();
	
	void LaunchProjectile(float Speed);

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

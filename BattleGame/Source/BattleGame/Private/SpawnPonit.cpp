// Individual Game.

#include "SpawnPonit.h"
#include "Engine/World.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USpawnPonit::USpawnPonit()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpawnPonit::BeginPlay()
{
	Super::BeginPlay();

	// SpawnedActor 生成的同时track it
	SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>(SpawnClass,GetComponentTransform());
	if (!SpawnedActor) return;
	//由于上面产生spawn使用了组件的世界位置，如果继续使用relativeTransform则是以世界位置为相对原点；所以统一使用worldTransform
	SpawnedActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	UGameplayStatics::FinishSpawningActor(SpawnedActor,GetComponentTransform());

}


// Called every frame
void USpawnPonit::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


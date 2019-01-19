// Individual Game.

#include "TankAIController.h"
#include "TankAimingComponent.h"

// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay() 
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto ControlledTank = GetPawn();
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }

	//move twords the player
	MoveToActor(PlayerTank,AcceptanceRadius);// TODO check radius is in cm
	
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	//Aim towards the player
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	
	AimingComponent->Fire();// TODO not every frame

}


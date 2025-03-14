// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "RB_MovingPlatform.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InterpToMovementComponent.h"




ARB_MovingPlatform::ARB_MovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = BoxCollider;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform Mesh"));
	PlatformMesh->SetupAttachment(RootComponent);

	Movement = CreateDefaultSubobject<UInterpToMovementComponent>(TEXT("Movement Component"));

	// Default parameters. **//
	Movement->Duration = 15.0f;
	Movement->bSweep = true;
	Movement->BehaviourType = EInterpToBehaviourType::PingPong;
}

void ARB_MovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	MovePlatform();
}

void ARB_MovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARB_MovingPlatform::MovePlatform()
{
	//** Setting up the control points for movement. **//
	Movement->ControlPoints.Add(FInterpControlPoint(FVector(0.0f, 0.0f, 0.0f), true));

	for (int i = 0; i < ThePath.Num(); i++)
	{
		//** Add Control Point relative to Platform position. **//
		Movement->ControlPoints.Add(FInterpControlPoint(ThePath[i], true));
	}

	Movement->FinaliseControlPoints();
}


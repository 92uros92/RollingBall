// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "BallPawn.h"



ABallPawn::ABallPawn()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABallPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABallPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABallPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


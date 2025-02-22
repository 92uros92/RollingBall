// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "SpawnEndGate.h"
#include "OpenEndGate.h"



ASpawnEndGate::ASpawnEndGate()
{

	PrimaryActorTick.bCanEverTick = true;

}

void ASpawnEndGate::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASpawnEndGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnEndGate::SpawnActor()
{
	AOpenEndGate* OpenEndGate = GetWorld()->SpawnActor<AOpenEndGate>(OpenEndGateClass, RootComponent->GetComponentLocation(), RootComponent->GetComponentRotation());
}


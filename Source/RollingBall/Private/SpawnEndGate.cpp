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
	if (!OpenEndGateClass)
	{
		UE_LOG(LogTemp, Error, TEXT("OpenEndGateClass is not set in BP_SpawnEndGate."));
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	SpawnParams.Owner = this;  // Set this Spawner as the owner

	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = FRotator::ZeroRotator;

	AOpenEndGate* OpenEndGate = GetWorld()->SpawnActor<AOpenEndGate>(OpenEndGateClass, SpawnLocation, SpawnRotation, SpawnParams);

	if (OpenEndGate)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawned Actor: %s"), *OpenEndGate->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to spawn actor."));
	}
}


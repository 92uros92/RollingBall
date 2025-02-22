// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnEndGate.generated.h"



class AOpenEndGate;

UCLASS()
class ROLLINGBALL_API ASpawnEndGate : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(EditAnywhere, Category = "SpawnActor")
	TSubclassOf<AOpenEndGate> OpenEndGateClass;

	// ******** FUNCTIONS ******** //

	ASpawnEndGate();

	virtual void Tick(float DeltaTime) override;

	void SpawnActor();

protected:

	virtual void BeginPlay() override;

};

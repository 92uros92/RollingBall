// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RB_MovingPlatform.generated.h"



class UBoxComponent;
class UStaticMeshComponent;
class UInterpToMovementComponent;


UCLASS()
class ROLLINGBALL_API ARB_MovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Path", meta = (ExposeOnSpawn = "true", MakeEditWidget = "true"))
	TArray<FVector> ThePath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
	USoundBase* PlatformSound;

	// ******** FUNCTIONS ******** //

	ARB_MovingPlatform();

	virtual void Tick(float DeltaTime) override;

	void MovePlatform();

protected:

	virtual void BeginPlay() override;

private:	

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UBoxComponent* BoxCollider;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UStaticMeshComponent* PlatformMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UInterpToMovementComponent* Movement;

};

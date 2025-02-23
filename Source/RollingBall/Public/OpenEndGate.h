// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OpenEndGate.generated.h"



class UBoxComponent;
class UParticleSystemComponent;
class ARollingBallGameMode;


UCLASS()
class ROLLINGBALL_API AOpenEndGate : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleInstanceOnly)
	ARollingBallGameMode* RollingBallGM;

	// ******** FUNCTIONS ******** //

	AOpenEndGate();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnTriggerBoxEnter(AActor* OverlappActor, AActor* OtherActor);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* EndTriggerBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UParticleSystemComponent* ParticleSystemComp;

	// ******** FUNCTIONS ******** //

	virtual void BeginPlay() override;

};

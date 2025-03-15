// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RB_BreakablePlatform.generated.h"



class UBoxComponent;
class UStaticMeshComponent;


UCLASS()
class ROLLINGBALL_API ARB_BreakablePlatform : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* BoxCollider;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* PlatformMesh;

	bool bIsPlatformFractured;

	// ******** FUNCTIONS ******** //

	ARB_BreakablePlatform();

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

private:	

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	void BreakPlatform();

	void AppearPlatform();

};

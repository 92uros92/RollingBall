// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "TeleportBox.generated.h"


class AActor;
class UArrowComponent;
class USoundBase;


UCLASS()
class ROLLINGBALL_API ATeleportBox : public ATriggerBox
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, Category = "Teleporter")
	ATeleportBox* OtherTeleporter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
	USoundBase* TeleportSound;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//FRotator ExitFacingDirection = FRotator(0.0f, 90.0f, 0.0f);

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Teleporter")
	//UArrowComponent* PawnLook;

	UPROPERTY()
	bool bIsTeleporting;

	// ******** FUNCTIONS ******** //

	ATeleportBox();

	UFUNCTION()
	void OnTeleporterEnter(AActor* OverlappActor, AActor* OtherActor);

	UFUNCTION()
	void OnTeleporterExit(AActor* OverlappActor, AActor* OtherActor);

protected:

	virtual void BeginPlay() override;
};

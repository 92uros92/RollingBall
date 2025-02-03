// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "TeleportBox.generated.h"


class AActor;
class UStaticMeshComponent;


UCLASS()
class ROLLINGBALL_API ATeleportBox : public ATriggerBox
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, Category = "Teleporter")
	ATeleportBox* OtherTeleporter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Teleporter")
	class UArrowComponent* PawnLook;

	UPROPERTY()
	bool bIsTeleporting;


	ATeleportBox();

	UFUNCTION()
	void OnTeleporterEnter(AActor* OverlappActor, AActor* OtherActor);

	UFUNCTION()
	void OnTeleporterExit(AActor* OverlappActor, AActor* OtherActor);

protected:

	virtual void BeginPlay() override;
};

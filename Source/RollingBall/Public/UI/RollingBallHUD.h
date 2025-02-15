// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RollingBallHUD.generated.h"

/**
 * 
 */
UCLASS()
class ROLLINGBALL_API ARollingBallHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	UPROPERTY()
	class UScreenWidget* OverlayWidget;

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UScreenWidget> OverlayWidgetClass;
};

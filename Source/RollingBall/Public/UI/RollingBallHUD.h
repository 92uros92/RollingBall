// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RollingBallHUD.generated.h"




UCLASS()
class ROLLINGBALL_API ARollingBallHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	UPROPERTY()
	class UScreenWidget* OverlayWidget;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> ScreenWidgetClass;

	// ******** FUNCTIONS ******** //

	ARollingBallHUD();

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	UFUNCTION()
	void SetCoinsCount(const int32 Value);

	UFUNCTION()
	void SetMaxCoins(const int32 Value);

	UFUNCTION(BlueprintCallable)
	void InitializeWidget(class ARollingBallGameMode* RunGameMode);


private:

	class UScreenWidget* ScreenWidget;
};

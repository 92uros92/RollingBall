// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RollingBallGameMode.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCoinsCountChanged, int32, CoinsCount);



UCLASS()
class ROLLINGBALL_API ARollingBallGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events")
	FOnCoinsCountChanged OnCoinsCountChanged;

	UPROPERTY(VisibleAnywhere, Category = "Score")
	int32 TotalCoins;

	UPROPERTY(VisibleInstanceOnly, Category = "Widget")
	class UScreenWidget* ScreenWidget;


	// ******** FUNCTIONS ******** //

	ARollingBallGameMode();

	UFUNCTION(BlueprintCallable)
	void CountCoin();

protected:

	virtual void BeginPlay() override;
};

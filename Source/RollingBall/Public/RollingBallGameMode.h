// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RollingBallGameMode.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCoinsCountChanged, int32, CoinsCount);


class UUserWidget;
class UScreenWidget;
class ARollingBallHUD;


UCLASS()
class ROLLINGBALL_API ARollingBallGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, Category = "Components")
	TSubclassOf<UUserWidget> EndWidgetClass;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events")
	FOnCoinsCountChanged OnCoinsCountChanged;

	UPROPERTY(VisibleAnywhere, Category = "Sccore")
	int32 TotalCoins;

	UPROPERTY(VisibleAnywhere, Category = "Sccore")
	int32 MaxCoins;

	UPROPERTY(BlueprintReadWRite, EditAnywhere, Category = "ActorsToFind")
	TSubclassOf<AActor> BlueprintClassToFind;

	UPROPERTY(BlueprintReadOnly, Category = "ActorsToFind")
	TArray<AActor*> ActorsToFind;

	UPROPERTY(VisibleInstanceOnly, Category = "Widget")
	UScreenWidget* ScreenWidget;

	UPROPERTY(VisibleInstanceOnly)
	ARollingBallHUD* RollingBallHUD;

	// ******** FUNCTIONS ******** //

	ARollingBallGameMode();

	UFUNCTION(BlueprintCallable)
	void CountCoin();

	void SetMaxSccore();

	UFUNCTION(BlueprintCallable)
	void GameOver();

protected:

	virtual void BeginPlay() override;
};

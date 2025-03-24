// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScreenWidget.generated.h"




DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameTimeChanged, float, GameTimeCount);


class UTextBlock;


UCLASS()
class ROLLINGBALL_API UScreenWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events")
	FOnGameTimeChanged OnGameTimeChanged;

	UPROPERTY(VisibleAnywhere, Category = "Time")
	float StartGameTime;

	UPROPERTY(VisibleAnywhere, Category = "Time")
	float EndGameTime;

	UPROPERTY(VisibleAnywhere, Category = "Time")
	float TotalGameTime;

	// ******** FUNCTIONS ******** //

	UFUNCTION(BlueprintCallable)
	void InitializeWidget(class ARollingBallGameMode* RunGameMode);

	UFUNCTION(BlueprintCallable)
	void SetCoinsCount(const int32 Value);

	UFUNCTION(BlueprintCallable)
	void SetMaxCoins(const int32 Value);

	//UFUNCTION(BlueprintCallable)
	//void SetGameTimeText();

	void EndGame();

	float GetElapsedGameTime() const;

protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CurrentCount;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* MaxCount;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* GameTimeText;

	//float GameTime;

	//FTimerHandle GameTimerHandle;

	// ******** FUNCTIONS ******** //

	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

	//virtual void NativeDestruct() override;
};

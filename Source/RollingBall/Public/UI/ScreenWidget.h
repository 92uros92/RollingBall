// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScreenWidget.generated.h"




class UTextBlock;


UCLASS()
class ROLLINGBALL_API UScreenWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	// ******** FUNCTIONS ******** //

	UFUNCTION(BlueprintCallable)
	void InitializeWidget(class ARollingBallGameMode* RunGameMode);

	UFUNCTION(BlueprintCallable)
	void SetCoinsCount(const int32 Value);

	UFUNCTION(BlueprintCallable)
	void SetMaxCoins(const int32 Value);

	UFUNCTION(BlueprintCallable)
	void SetGameTimeText();

protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CurrentCount;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* MaxCount;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* GameTimeText;

	int32 GameTime;

	FTimerHandle GameTimerHandle;

	// ******** FUNCTIONS ******** //

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;
};

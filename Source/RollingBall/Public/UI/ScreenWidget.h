// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScreenWidget.generated.h"




UCLASS()
class ROLLINGBALL_API UScreenWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void InitializeWidget(class ARollingBallGameMode* RunGameMode);

	UFUNCTION(BlueprintCallable)
	void SetCoinsCount(const int32 Count);

protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* CoinsCount;

	// ******** FUNCTIONS ******** //

	virtual void NativeConstruct() override;
};

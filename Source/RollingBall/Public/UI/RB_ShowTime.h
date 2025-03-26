// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RB_ShowTime.generated.h"



class UTextBlock;
class ARollingBallGameMode;
class URB_SaveGame;


UCLASS()
class ROLLINGBALL_API URB_ShowTime : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ShowTimeText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* DescriptionText;

	// ******** FUNCTIONS ******** //

	UFUNCTION(BlueprintCallable)
	void InitializeWidget(ARollingBallGameMode* RunGameMode);

	UFUNCTION(BlueprintCallable)
	void SetGameTimeCount(int32 TimeCount);

protected:

	UPROPERTY(BlueprintReadOnly)
	URB_SaveGame* RB_SaveGame;
};

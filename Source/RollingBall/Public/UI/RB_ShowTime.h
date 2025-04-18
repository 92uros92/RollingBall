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

	int32 TotalSecond;
	int32 minutes;
	int32 seconds;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ShowTimeText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* DescriptionText;

	UPROPERTY(BlueprintReadOnly, Category = "MapTime")
	FString Level1Map = TEXT("FirstLevel");

	// ******** FUNCTIONS ******** //

	UFUNCTION(BlueprintCallable)
	void SetGameTimeCount();

protected:

	UPROPERTY(BlueprintReadOnly)
	URB_SaveGame* LoadedGameInstance;

};

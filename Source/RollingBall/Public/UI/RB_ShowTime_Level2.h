// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RB_ShowTime_Level2.generated.h"



class UTextBlock;
class ARollingBallGameMode;
class URB_SaveGame;


UCLASS()
class ROLLINGBALL_API URB_ShowTime_Level2 : public UUserWidget
{
	GENERATED_BODY()
	
public:

	int32 TotalSecond;
	int32 minutes;
	int32 seconds;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ShowTimeText_Level2;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* DescriptionText_Level2;

	UPROPERTY(BlueprintReadOnly, Category = "MapTime")
	FString Level2Map = TEXT("SecondLevel");

	// ******** FUNCTIONS ******** //

	UFUNCTION(BlueprintCallable)
	void SetGameTimeCount();

protected:

	UPROPERTY(BlueprintReadOnly)
	URB_SaveGame* LoadedGameInstance;

};

// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndWidget.generated.h"



class UTextBlock;


UCLASS()
class ROLLINGBALL_API UEndWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ShowEndTimeText;

	int32 EndTime;

	// ******** FUNCTIONS ******** //

	UFUNCTION(BlueprintCallable)
	void SetShowEndTime();
};

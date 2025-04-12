// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "UI/EndWidget.h"
#include "RollingBallGameMode.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"




void UEndWidget::SetShowEndTime()
{
	ARollingBallGameMode* GameMode = Cast<ARollingBallGameMode>(UGameplayStatics::GetGameMode(this));
	if (GameMode && ShowEndTimeText)
	{
		EndTime = GameMode->EndGameTime; //OnGameTimeChanged
		int32 TotalSecond = EndTime;
		int32 minutes = TotalSecond / 60;
		int32 seconds = TotalSecond % 60;

		FString TimeString = FString::Printf(TEXT("Time: %02d:%02d"), minutes, seconds);
		ShowEndTimeText->SetText(FText::FromString(TimeString));
	}
}

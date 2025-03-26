// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "UI/RB_ShowTime.h"
#include "RollingBallGameMode.h"
#include "RB_SaveGame.h"
#include "Components/TextBlock.h"




void URB_ShowTime::InitializeWidget(ARollingBallGameMode* RunGameMode)
{
	if (RunGameMode)
	{
		int32 TotalSecond = RB_SaveGame->GameTime;
		int32 minutes = TotalSecond / 60;
		int32 seconds = TotalSecond % 60;

		FString TimeString = FString::Printf(TEXT("%i:%i"), minutes, seconds);
		ShowTimeText->SetText(FText::FromString(TimeString));

		RunGameMode->OnGameTimeChanged.AddDynamic(this, &URB_ShowTime::SetGameTimeCount);
	}
}

void URB_ShowTime::SetGameTimeCount(int32 TimeCount)
{
	int32 TotalSecond = RB_SaveGame->GameTime;
	int32 minutes = TotalSecond / 60;
	int32 seconds = TotalSecond % 60;

	FString TimeString = FString::Printf(TEXT("%i:%i"), minutes, seconds);
	ShowTimeText->SetText(FText::FromString(TimeString));
}

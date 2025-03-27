// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "UI/RB_ShowTime.h"
#include "RollingBallGameMode.h"
#include "RB_SaveGame.h"
#include "Components/TextBlock.h"





void URB_ShowTime::NativeConstruct()
{
	if (SaveGame)
	{
		TotalSecond = SaveGame->GameTime;
		//minutes = TotalSecond / 60;
		//seconds = TotalSecond % 60;
	}
}

void URB_ShowTime::InitializeWidget(ARollingBallGameMode* RunGameMode)
{
	if (RunGameMode)
	{
		FString TimeString = FString::Printf(TEXT("%d"), SaveGame->GameTime);
		ShowTimeText->SetText(FText::FromString(TimeString));

		RunGameMode->OnGameTimeChanged.AddDynamic(this, &URB_ShowTime::SetGameTimeCount);
	}
}

void URB_ShowTime::SetGameTimeCount(int32 TimeCount)
{
	FString TimeString = FString::Printf(TEXT("%d"), SaveGame->GameTime);
	ShowTimeText->SetText(FText::FromString(TimeString));
}

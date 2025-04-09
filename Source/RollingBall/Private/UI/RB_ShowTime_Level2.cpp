// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "UI/RB_ShowTime_Level2.h"
#include "RollingBallGameMode.h"
#include "RB_SaveGame.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"




void URB_ShowTime_Level2::SetGameTimeCount()
{
	SaveGameInstance = Cast<URB_SaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("GameTimeSlot"), 0));

	if (SaveGameInstance)
	{
		//** Find SecondLevel map name **//
		FMapTimeData* CurrentEntry = SaveGameInstance->MapTimes.FindByPredicate([&](const FMapTimeData& Entry)
			{
				return Entry.MapName == Level2Map;
			});

		//** If found map name in MapTimes array then show the time from SecondLevel **//
		if (CurrentEntry)
		{
			for (const FMapTimeData& Entry : SaveGameInstance->MapTimes)
			{
				TotalSecond = Entry.GameTime;
				minutes = TotalSecond / 60;
				seconds = TotalSecond % 60;

				FString TimeString = FString::Printf(TEXT("%02d:%02d"), minutes, seconds);
				ShowTimeText_Level2->SetText(FText::FromString(TimeString));
			}
		}
	}

}

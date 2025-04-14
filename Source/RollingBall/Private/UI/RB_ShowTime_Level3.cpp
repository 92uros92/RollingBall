// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "UI/RB_ShowTime_Level3.h"
#include "RollingBallGameMode.h"
#include "RB_SaveGame.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"




void URB_ShowTime_Level3::SetGameTimeCount()
{
	SaveGameInstance = Cast<URB_SaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("GameTimeSlot"), 0));

	if (SaveGameInstance)
	{
		//** Find ThirdLevel map name **//
		FMapTimeData* CurrentEntry = SaveGameInstance->MapTimes.FindByPredicate([&](const FMapTimeData& Entry)
			{
				return Entry.MapName == Level3Map;
			});

		//** If found map name in MapTimes array then show the time from ThirdLevel **//
		if (CurrentEntry)
		{
			for (const FMapTimeData& Entry : SaveGameInstance->MapTimes)
			{
				TotalSecond = Entry.GameTime;
				minutes = TotalSecond / 60;
				seconds = TotalSecond % 60;

				FString TimeString = FString::Printf(TEXT("%02d:%02d"), minutes, seconds);
				ShowTimeText_Level3->SetText(FText::FromString(TimeString));
			}
		}
	}


}

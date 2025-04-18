// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "UI/RB_ShowTime_Level3.h"
#include "RollingBallGameMode.h"
#include "RB_SaveGame.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"




void URB_ShowTime_Level3::SetGameTimeCount()
{
	LoadedGameInstance = Cast<URB_SaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("GameTimeSlot"), 0));

	if (LoadedGameInstance)
	{
		TMap<FString, int32> Times = LoadedGameInstance->MapTimes;

		for (const auto& Entry : Times)
		{
			if (Entry.Key == Level3Map)
			{
				TotalSecond = Entry.Value;
				minutes = TotalSecond / 60;
				seconds = TotalSecond % 60;

				//FString TimeString = FString::Printf(TEXT("%i:%i"), minutes, seconds);
				FString TimeString = FString::Printf(TEXT("%02d:%02d"), minutes, seconds);
				ShowTimeText_Level3->SetText(FText::FromString(TimeString));
			}
		}
	}


}

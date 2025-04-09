// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "UI/RB_ShowTime.h"
#include "RollingBallGameMode.h"
#include "RB_SaveGame.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"





void URB_ShowTime::SetGameTimeCount()
{
	SaveGameInstance = Cast<URB_SaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("GameTimeSlot"), 0));

	if (SaveGameInstance)
	{
		//** Find FirstLevel map name **//
		FMapTimeData* CurrentEntry = SaveGameInstance->MapTimes.FindByPredicate([&](const FMapTimeData& Entry)
			{
				return Entry.MapName == Level1Map;
			});

		//** If found map name in MapTimes array then show the time from FirstLevel **//
		if (CurrentEntry)
		{
			for (const FMapTimeData& Entry : SaveGameInstance->MapTimes)
			{
				TotalSecond = Entry.GameTime;
				minutes = TotalSecond / 60;
				seconds = TotalSecond % 60;

				//FString TimeString = FString::Printf(TEXT("%i:%i"), minutes, seconds);
				FString TimeString = FString::Printf(TEXT("%02d:%02d"), minutes, seconds);
				ShowTimeText->SetText(FText::FromString(TimeString));
			}
		}
	}
}

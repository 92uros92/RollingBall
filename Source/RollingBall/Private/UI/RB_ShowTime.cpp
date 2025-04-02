// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "UI/RB_ShowTime.h"
#include "RollingBallGameMode.h"
#include "RB_SaveGame.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"





void URB_ShowTime::SetGameTimeCount()
{
	SaveGame = Cast<URB_SaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("GameTimeSlot"), 0));

	if (SaveGame)
	{
		TotalSecond = SaveGame->GameTime;
		minutes = TotalSecond / 60;
		seconds = TotalSecond % 60;

		FString TimeString = FString::Printf(TEXT("%i:%i"), minutes, seconds);
		ShowTimeText->SetText(FText::FromString(TimeString));
	}
	
}

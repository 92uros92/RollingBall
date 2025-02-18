// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "RollingBallGameMode.h"
#include "BallPawn.h"
#include "UI/ScreenWidget.h"
#include "UI/RollingBallHUD.h"
#include "Kismet/GameplayStatics.h"




ARollingBallGameMode::ARollingBallGameMode()
{
	TotalCoins = 0;
}

void ARollingBallGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Find all Blueprint Actors of specific class
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), BlueprintClassToFind, ActorsToFind);
}

void ARollingBallGameMode::CountCoin()
{
	RollingBallHUD = Cast<ARollingBallHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	if (RollingBallHUD)
	{
		TotalCoins += 1;
		//UE_LOG(LogTemp, Warning, TEXT("Total Coins: %d"), TotalCoins);

		OnCoinsCountChanged.Broadcast(TotalCoins);

		RollingBallHUD->SetCoinsCount(TotalCoins);

		// If pick up all coins then call win widget
		if (TotalCoins == ActorsToFind.Num())
		{
			//UE_LOG(LogTemp, Warning, TEXT("You Won!!"));
			GameOver();
		}
	}
}

void ARollingBallGameMode::SetMaxSccore()
{
}

void ARollingBallGameMode::GameOver()
{
	if (IsValid(EndWidgetClass))
	{
		UUserWidget* Widget = CreateWidget(GetWorld(), EndWidgetClass);

		if (Widget)
		{
			Widget->AddToViewport();
		}
	}
}

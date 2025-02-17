// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "RollingBallGameMode.h"
#include "BallPawn.h"
#include "UI/ScreenWidget.h"
#include "UI/RollingBallHUD.h"




ARollingBallGameMode::ARollingBallGameMode()
{
	TotalCoins = 0;
}

void ARollingBallGameMode::BeginPlay()
{
	Super::BeginPlay();

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
	}
}


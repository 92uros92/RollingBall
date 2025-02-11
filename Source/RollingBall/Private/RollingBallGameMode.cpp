// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "RollingBallGameMode.h"




ARollingBallGameMode::ARollingBallGameMode()
{
	TotalCoins = 0;
}

void ARollingBallGameMode::CountCoin()
{
	TotalCoins += 1;
	//UE_LOG(LogTemp, Warning, TEXT("Total Coins: %d"), TotalCoins);

	OnCoinsCountChanged.Broadcast(TotalCoins);
}

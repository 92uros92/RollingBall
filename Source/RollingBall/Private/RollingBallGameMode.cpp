// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "RollingBallGameMode.h"
#include "BallPawn.h"
#include "OpenEndGate.h"
#include "SpawnEndGate.h"
#include "UI/ScreenWidget.h"
#include "UI/RollingBallHUD.h"
#include "Kismet/GameplayStatics.h"




ARollingBallGameMode::ARollingBallGameMode()
{
	TotalCoins = 0;
	MaxCoins = 0;
}

void ARollingBallGameMode::BeginPlay()
{
	Super::BeginPlay();

	RollingBallHUD = Cast<ARollingBallHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	if (RollingBallHUD)
	{
		ScreenWidget = Cast<UScreenWidget>(CreateWidget(GetWorld(), ScreenWidgetClass));
		check(ScreenWidget);

		ScreenWidget->InitializeWidget(this);

		//** Find all Blueprint Actors of specific class **//
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), BlueprintClassToFind, ActorsToFind);
		MaxCoins = ActorsToFind.Num();

		OnMaxCoinsCountChanged.Broadcast(MaxCoins);
	
		RollingBallHUD->SetMaxCoins(MaxCoins);
	}
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

		//** If pick up all coins then spawn EndGate actor. **//
		if (TotalCoins == MaxCoins)
		{
			TriggerEndGate();
		}
	}
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

void ARollingBallGameMode::TriggerEndGate()
{
	UWorld* World = GetWorld();
	if (!World) return;

	// Find all actors of class ASpawnEndGate
	TArray<AActor*> FoundSpawners;
	UGameplayStatics::GetAllActorsOfClass(World, ASpawnEndGate::StaticClass(), FoundSpawners);

	if (FoundSpawners.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No SpawnEndGate actor found in the world."));
		return;
	}

	// Call the spawn function on the first found spawner
	SpawnEndGate = Cast<ASpawnEndGate>(FoundSpawners[0]);
	if (SpawnEndGate)
	{
		SpawnEndGate->SpawnActor();
		UE_LOG(LogTemp, Warning, TEXT("Triggered SpawnEndGate actor."));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to cast FoundSpawners to SpawnEndGate."));
	}
}

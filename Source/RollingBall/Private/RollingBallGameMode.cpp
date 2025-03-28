// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "RollingBallGameMode.h"
#include "BallPawn.h"
#include "OpenEndGate.h"
#include "SpawnEndGate.h"
#include "RB_SaveGame.h"
#include "UI/ScreenWidget.h"
#include "UI/RollingBallHUD.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"




ARollingBallGameMode::ARollingBallGameMode()
{
	TotalCoins = 0;

	StartGameTime = 0;
	EndGameTime = 0;
	bGameEnded = false;
}

void ARollingBallGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//** Update elapsed time but only if game is running **//
	if (!bGameEnded)
	{
		int32 ElapsedTime = GetElapsedGameTime();
		UE_LOG(LogTemp, Log, TEXT("Elapsed Time: %i seconds"), ElapsedTime);
	}
}

void ARollingBallGameMode::BeginPlay()
{
	Super::BeginPlay();

	LoadGameTime();

	//** Store the game time when start **//
	StartGameTime = GetWorld()->GetTimeSeconds();

	//** Find all Blueprint Actors of specific class **//
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), BlueprintClassToFind, ActorsToFind);
	MaxCoins = ActorsToFind.Num();
	
	if (ScreenWidgetClass)
	{
		ScreenWidget = Cast<UScreenWidget>(CreateWidget(GetWorld(), ScreenWidgetClass));
		
		//** If the ScreenWidget is valid, initialize it and add it on viewport. **//
		if (IsValid(ScreenWidget))
		{
			ScreenWidget->InitializeWidget(this);

			ScreenWidget->AddToViewport();
		}
	}
		
	OnMaxCoinsCountChanged.Broadcast(MaxCoins);
	
	ScreenWidget->SetMaxCoins(MaxCoins);
}

void ARollingBallGameMode::CountCoin()
{
	if (ScreenWidget)
	{
		TotalCoins += 1;
		//UE_LOG(LogTemp, Warning, TEXT("Total Coins: %d"), TotalCoins);

		OnCoinsCountChanged.Broadcast(TotalCoins);

		ScreenWidget->SetCoinsCount(TotalCoins);

		//** If pick up all coins then spawn EndGate actor. **//
		if (TotalCoins == MaxCoins)
		{
			TriggerEndGate();

			GoToEndCamera();

			//** After 3 second when call GoToEndCamera() call GoToPlayerCamera **//
			FTimerHandle MemberTimerHandle;
			GetWorld()->GetTimerManager().SetTimer(MemberTimerHandle, this, &ARollingBallGameMode::GoToPlayerCamera, 3.0f, false);
		}
	}
}

void ARollingBallGameMode::GameOver()
{
	EndGame();

	SaveGameTime();

	if (IsValid(ScreenWidget))
	{
		ScreenWidget->RemoveFromParent();
	}

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

	//** Find all actors of class ASpawnEndGate. **//
	TArray<AActor*> FoundSpawners;
	UGameplayStatics::GetAllActorsOfClass(World, ASpawnEndGate::StaticClass(), FoundSpawners);

	if (FoundSpawners.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No SpawnEndGate actor found in the world."));
		return;
	}

	//** Call the spawn function on the first found spawner. **//
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

void ARollingBallGameMode::GoToEndCamera()
{
	//Find the actor that handles control for the local player. **//
	APlayerController* MyPlayerController = UGameplayStatics::GetPlayerController(this, 0);

	//** Find all actors with tag EndCamera. **//
	TArray<AActor*> FocusCamera;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("EndCamera"), FocusCamera);

	//** Set camera view for the actor whose tag is EndCamera. **//
	MyPlayerController->SetViewTargetWithBlend(FocusCamera[0], 0.0f);
}

void ARollingBallGameMode::GoToPlayerCamera()
{
	//Find the actor that handles control for the local player. **//
	APlayerController* MyPlayerController = UGameplayStatics::GetPlayerController(this, 0);

	//** Set camera view back to player camera. **//
	MyPlayerController->SetViewTargetWithBlend(MyPlayerController->GetPawn(), 0.0f);
}


void ARollingBallGameMode::EndGame()
{
	if (!bGameEnded)
	{
		bGameEnded = true;

		//** Store the time when the game ends **//
		EndGameTime = GetWorld()->GetTimeSeconds();

		TotalGameTime = GetElapsedGameTime();

		OnGameTimeChanged.Broadcast(TotalGameTime);

		SaveGameTime();

		UE_LOG(LogTemp, Warning, TEXT("Total Game Time: %i seconds"), TotalGameTime);
	}
}

float ARollingBallGameMode::GetElapsedGameTime() const
{
	return bGameEnded ? (EndGameTime - StartGameTime) : (GetWorld()->GetTimeSeconds() - StartGameTime);
}

void ARollingBallGameMode::SaveGameTime()
{
	SaveGameInstance = Cast<URB_SaveGame>(UGameplayStatics::CreateSaveGameObject(URB_SaveGame::StaticClass()));

	if (SaveGameInstance)
	{
		SaveGameInstance->GameTime = TotalGameTime;

		OnGameTimeChanged.Broadcast(TotalGameTime);

		UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("GameTimeSlot"), 0);
	}
}

void ARollingBallGameMode::LoadGameTime()
{
	if (UGameplayStatics::DoesSaveGameExist(TEXT("GameTimeSlot"), 0))
	{
		SaveGameInstance = Cast<URB_SaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("GameTimeSlot"), 0));

		if (SaveGameInstance)
		{
			TotalGameTime = SaveGameInstance->GameTime;

			UE_LOG(LogTemp, Warning, TEXT("SavedGameTime: %i"), TotalGameTime);
		}
	}
	else
	{
		TotalGameTime = 0;
	}
}


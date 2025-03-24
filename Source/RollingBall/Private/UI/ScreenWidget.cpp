// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "UI/ScreenWidget.h"
#include "RollingBallGameMode.h"
#include "UI/RollingBallHUD.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"




void UScreenWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	StartGameTime = 0.0f;
	EndGameTime = 0.0f;
}

void UScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//** Store the game time when start **//
	StartGameTime = GetWorld()->GetTimeSeconds();
}

//void UScreenWidget::NativeDestruct()
//{
//	Super::NativeDestruct();
//
//	//** Clear the timer **//
//	GetWorld()->GetTimerManager().ClearTimer(GameTimerHandle);
//}

void UScreenWidget::InitializeWidget(ARollingBallGameMode* RunGameMode)
{
	if (RunGameMode)
	{
		CurrentCount->SetText(FText::AsNumber(0));

		MaxCount->SetText(FText::AsNumber(0));

		FString TimeString = FString::Printf(TEXT("Time: %.1f s"), StartGameTime);
		GameTimeText->SetText(FText::FromString(TimeString));

		RunGameMode->OnCoinsCountChanged.AddDynamic(this, &UScreenWidget::SetCoinsCount);
		RunGameMode->OnMaxCoinsCountChanged.AddDynamic(this, &UScreenWidget::SetMaxCoins);
		//RunGameMode->OnGameTimeChanged.AddDynamic(this, &UScreenWidget::SetGameTimeText);
	}
}

void UScreenWidget::SetCoinsCount(const int32 Value)
{
	CurrentCount->SetText(FText::AsNumber(Value));
}

void UScreenWidget::SetMaxCoins(const int32 Value)
{
	MaxCount->SetText(FText::AsNumber(Value));
}

//void UScreenWidget::SetGameTimeText()
//{
//
//	//ElapsedTime = GetWorld()->GetTimeSeconds();
//	/*ElapsedTime += 1.0f;*/
//
//	ARollingBallGameMode* GameMode = Cast<ARollingBallGameMode>(UGameplayStatics::GetGameMode(this));
//	if (GameMode && GameTimeText)
//	{
//		float GameTime = GameMode->GetElapsedGameTime();
//		GameTimeText->SetText(FText::FromString(FString::Printf(TEXT("Game Time: %.1f s"), GameTime)));
//	}
//}

void UScreenWidget::EndGame()
{
	//** Store the time when the game ends **//
	EndGameTime = GetWorld()->GetTimeSeconds();

	TotalGameTime = GetElapsedGameTime();

	UE_LOG(LogTemp, Warning, TEXT("Total Game Time: %f seconds"), TotalGameTime);
}

float UScreenWidget::GetElapsedGameTime() const
{
	return (EndGameTime > 0.0f) ? (EndGameTime - StartGameTime) : (GetWorld()->GetTimeSeconds() - StartGameTime);
}


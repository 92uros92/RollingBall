// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "UI/ScreenWidget.h"
#include "RollingBallGameMode.h"
#include "UI/RollingBallHUD.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"




void UScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//** Start timer to update game time every 1 second **//
	GetWorld()->GetTimerManager().SetTimer(GameTimerHandle, this, &UScreenWidget::SetGameTimeText, 1.0f, true);
}

void UScreenWidget::NativeDestruct()
{
	Super::NativeDestruct();

	//** Clear the timer **//
	GetWorld()->GetTimerManager().ClearTimer(GameTimerHandle);
}

void UScreenWidget::InitializeWidget(ARollingBallGameMode* RunGameMode)
{
	if (RunGameMode)
	{
		CurrentCount->SetText(FText::AsNumber(0));

		MaxCount->SetText(FText::AsNumber(0));

		RunGameMode->OnCoinsCountChanged.AddDynamic(this, &UScreenWidget::SetCoinsCount);
		RunGameMode->OnMaxCoinsCountChanged.AddDynamic(this, &UScreenWidget::SetMaxCoins);
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

void UScreenWidget::SetGameTimeText()
{

	//ElapsedTime = GetWorld()->GetTimeSeconds();
	/*ElapsedTime += 1.0f;*/

	ARollingBallGameMode* GameMode = Cast<ARollingBallGameMode>(UGameplayStatics::GetGameMode(this));
	if (GameMode && GameTimeText)
	{
		GameTime = GameMode->GetElapsedGameTime();
		int32 TotalSecond = GameTime;
		int32 minutes = TotalSecond / 60;
		int32 seconds = TotalSecond % 60;

		FString TimeString = FString::Printf(TEXT("Time: %i:%i"), minutes, seconds);
		GameTimeText->SetText(FText::FromString(TimeString));
	}
}

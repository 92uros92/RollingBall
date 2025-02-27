// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "UI/ScreenWidget.h"
#include "RollingBallGameMode.h"
#include "UI/RollingBallHUD.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"




void UScreenWidget::NativeConstruct()
{
	
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


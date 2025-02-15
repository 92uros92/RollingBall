// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "UI/ScreenWidget.h"
#include "RollingBallGameMode.h"
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
		CoinsCount->SetText(FText::AsNumber(0));

		RunGameMode->OnCoinsCountChanged.AddDynamic(this, &UScreenWidget::SetCoinsCount);
	}
}

void UScreenWidget::SetCoinsCount(const int32 Count)
{
	CoinsCount->SetText(FText::AsNumber(Count));
}


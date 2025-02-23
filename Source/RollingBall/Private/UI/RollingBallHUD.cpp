// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "UI/RollingBallHUD.h"
#include "UI/ScreenWidget.h"
#include "RollingBallGameMode.h"




ARollingBallHUD::ARollingBallHUD()
{

}

void ARollingBallHUD::DrawHUD()
{
	Super::DrawHUD();

	
}

void ARollingBallHUD::BeginPlay()
{
	Super::BeginPlay();

	if (ScreenWidgetClass)
	{
		ScreenWidget = CreateWidget<UScreenWidget>(GetWorld(), ScreenWidgetClass);

		if (IsValid(ScreenWidget))
		{
			ScreenWidget->AddToViewport();
		}
	}
}

void ARollingBallHUD::SetCoinsCount(const int32 Value)
{
	if (ScreenWidget)
	{
		ScreenWidget->SetCoinsCount(Value);
	}
}

void ARollingBallHUD::SetMaxCoins(const int32 Value)
{
	if (ScreenWidget)
	{
		ScreenWidget->SetMaxCoins(Value);
	}
}

void ARollingBallHUD::InitializeWidget(ARollingBallGameMode* RunGameMode)
{
	if (ScreenWidget)
	{
		ScreenWidget->InitializeWidget(RunGameMode);
	}
}

// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "UI/RollingBallHUD.h"
#include "UI/ScreenWidget.h"




void ARollingBallHUD::InitializeOverlay(ARollingBallGameMode* RunGameMode)
{
	// zakljuèi HUD, tako da prikaže na zaslonu

	UUserWidget* Widget = CreateWidget<UScreenWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
}

void ARollingBallHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = CreateWidget<UScreenWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
}

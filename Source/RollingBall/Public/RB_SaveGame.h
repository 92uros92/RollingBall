// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RB_SaveGame.generated.h"





UCLASS()
class ROLLINGBALL_API URB_SaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Time")
	int32 GameTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Maps")
	FString MapName;

	// ******** FUNCTIONS ******** //

	URB_SaveGame();
};

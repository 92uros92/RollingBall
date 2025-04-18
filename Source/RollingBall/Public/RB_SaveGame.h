// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RB_SaveGame.generated.h"




USTRUCT(BlueprintType)
struct FMapTimeData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapTime")
	int32 GameTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapTime")
	FString MapName;

};

UCLASS()
class ROLLINGBALL_API URB_SaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapTime")
	//TArray<FMapTimeData> MapTimes;

	// Map of level names to play times (in seconds)
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TMap<FString, int32> MapTimes;

	// ******** FUNCTIONS ******** //

	URB_SaveGame();
};

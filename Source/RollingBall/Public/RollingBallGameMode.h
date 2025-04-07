// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RollingBallGameMode.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCoinsCountChanged, int32, CoinsCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxCoinsCountChanged, int32, MaxCoinsCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameTimeChanged, int32, GameTimeCount);



class UUserWidget;
class UScreenWidget;
class ARollingBallHUD;
class AOpenEndGate;
class ASpawnEndGate;
class URB_SaveGame;


UCLASS()
class ROLLINGBALL_API ARollingBallGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, Category = "Components")
	TSubclassOf<UUserWidget> EndWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Components")
	TSubclassOf<UUserWidget> ScreenWidgetClass;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events")
	FOnCoinsCountChanged OnCoinsCountChanged;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events")
	FOnMaxCoinsCountChanged OnMaxCoinsCountChanged;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events")
	FOnGameTimeChanged OnGameTimeChanged;

	UPROPERTY(VisibleInstanceOnly, Category = "SpawnActor")
	ASpawnEndGate* SpawnEndGate;

	UPROPERTY(VisibleAnywhere, Category = "Sccore")
	int32 TotalCoins;

	UPROPERTY(VisibleAnywhere, Category = "Sccore")
	int32 MaxCoins;

	UPROPERTY(BlueprintReadWRite, EditAnywhere, Category = "ActorsToFind")
	TSubclassOf<AActor> BlueprintClassToFind;

	UPROPERTY(BlueprintReadOnly, Category = "ActorsToFind")
	TArray<AActor*> ActorsToFind;

	UPROPERTY(VisibleInstanceOnly, Category = "Widget")
	UScreenWidget* ScreenWidget;

	UPROPERTY(VisibleInstanceOnly, Category = "Widget")
	ARollingBallHUD* RollingBallHUD;

	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	URB_SaveGame* SaveGameInstance;

	UPROPERTY(VisibleAnywhere, Category = "Time")
	int32 StartGameTime;

	UPROPERTY(VisibleAnywhere, Category = "Time")
	int32 EndGameTime;

	UPROPERTY(VisibleAnywhere, Category = "Time")
	int32 TotalGameTime;

	bool bGameEnded;

	UPROPERTY(BlueprintReadOnly, Category = "MapTime")
	FString CurrentMap;

	//UPROPERTY(BlueprintReadOnly, Category = "MapTime")
	//int32 MapTime;

	//UPROPERTY(BlueprintReadOnly, Category = "MapTime")
	//TSoftObjectPtr<UWorld> DefaultMap;

	//UPROPERTY(BlueprintReadOnly, Category = "MapTime")
	//TMap<TSoftObjectPtr<UWorld>, int32> Maps;

	// ******** FUNCTIONS ******** //

	ARollingBallGameMode();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void CountCoin();

	UFUNCTION(BlueprintCallable)
	void GameOver();

	void TriggerEndGate();

	void GoToEndCamera();

	void GoToPlayerCamera();

	UFUNCTION(BlueprintCallable)
	void SaveGameTime();

	UFUNCTION(BlueprintCallable)
	void LoadGameTime();

	void EndGame();

	float GetElapsedGameTime() const;

protected:

	virtual void BeginPlay() override;
};

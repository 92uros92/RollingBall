// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "SaveGameSubsystem.h"
#include "RB_SaveGame.h"
#include "SaveGameInterface.h"
#include "Kismet/GameplayStatics.h"





void USaveGameSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	SaveSlotName = TEXT("GameTimeSlot");

	if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0))
	{
		CurrentSaveGame = Cast<URB_SaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	}
	else
	{
		CurrentSaveGame = CastChecked<URB_SaveGame>(UGameplayStatics::CreateSaveGameObject(URB_SaveGame::StaticClass()));
	}
}

void USaveGameSubsystem::SaveGame()
{

}

void USaveGameSubsystem::LoadGame()
{

}

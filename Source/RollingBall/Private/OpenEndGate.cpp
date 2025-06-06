// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "OpenEndGate.h"
#include "RollingBallGameMode.h"
#include "BallPawn.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Controller.h"




AOpenEndGate::AOpenEndGate()
{
	PrimaryActorTick.bCanEverTick = true;

	EndTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("EndTriggerBox"));
	SetRootComponent(EndTriggerBox);
	
	ParticleSystemComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComp"));
	ParticleSystemComp->SetupAttachment(EndTriggerBox);


	OnActorBeginOverlap.AddDynamic(this, &AOpenEndGate::OnTriggerBoxEnter);
}

void AOpenEndGate::BeginPlay()
{
	Super::BeginPlay();
	
}

void AOpenEndGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOpenEndGate::OnTriggerBoxEnter(AActor* OverlappActor, AActor* OtherActor)
{
	if (OtherActor && OtherActor != this)
	{
		RollingBallGM = Cast<ARollingBallGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

		if (RollingBallGM)
		{
			RollingBallGM->GameOver();
		}

		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			BallPawn = PlayerController->GetPawn();

			if (BallPawn)
			{
				if (EndSound)
				{
					UGameplayStatics::PlaySoundAtLocation(GetWorld(), EndSound, GetActorLocation());
				}

				BallPawn->DisableInput(PlayerController);
				BallPawn->Destroy();
			}
		}

		UE_LOG(LogTemp, Warning, TEXT("Level finished!"));
	}
}

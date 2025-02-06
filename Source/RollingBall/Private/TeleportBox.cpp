// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "TeleportBox.h"
#include "BallPawn.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"




ATeleportBox::ATeleportBox()
{
	PawnLook = CreateDefaultSubobject<UArrowComponent>(TEXT("PawnLook"));

	OnActorBeginOverlap.AddDynamic(this, &ATeleportBox::OnTeleporterEnter);
	OnActorEndOverlap.AddDynamic(this, &ATeleportBox::OnTeleporterExit);

	bIsTeleporting = false;
}

void ATeleportBox::BeginPlay()
{
	Super::BeginPlay();
}

void ATeleportBox::OnTeleporterEnter(AActor* OverlappActor, AActor* OtherActor)
{
	if (OtherActor && OtherActor != this)
	{
		if (OtherTeleporter)
		{
			ABallPawn* MyPawn = Cast<ABallPawn>(OtherActor);

			if (MyPawn && !OtherTeleporter->bIsTeleporting)
			{
				bIsTeleporting = true;

				//FTransform NewTransform = 
				//PawnLook->SetWorldTransform(OtherTeleporter->PawnLook->GetComponentRotation(), 0.0f, 0);

				MyPawn->SetActorRotation(OtherTeleporter->PawnLook->GetComponentRotation());
				MyPawn->GetController()->SetControlRotation(PawnLook->GetComponentRotation());

				MyPawn->SetActorLocation(OtherTeleporter->GetActorLocation());

				/*
				
				MyPawn->SetActorRotation(OtherTeleporter->GetActorRotation());
				MyPawn->GetController()->SetControlRotation(MyPawn->GetActorRotation());

				MyPawn->SetActorLocation(OtherTeleporter->GetActorLocation());

				*/
			}
		}
	}
}

void ATeleportBox::OnTeleporterExit(AActor* OverlappActor, AActor* OtherActor)
{
	if (OtherActor && OtherActor != this)
	{
		if (OtherTeleporter && !bIsTeleporting)
		{
			OtherTeleporter->bIsTeleporting = false;

			// Always turn in one direction
		}
	}
}

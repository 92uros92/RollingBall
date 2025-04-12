// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "TeleportBox.h"
#include "BallPawn.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"




ATeleportBox::ATeleportBox()
{
	PawnLook = CreateDefaultSubobject<UArrowComponent>(TEXT("PawnLook"));
	PawnLook->SetupAttachment(RootComponent);  // Attach to root
	PawnLook->ArrowSize = 2.0f;                // Optional: make it bigger in editor
	PawnLook->SetRelativeLocation(FVector(0, 0, 20));  // Optional: raise it above the box

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
				if (TeleportSound)
				{
					UGameplayStatics::PlaySoundAtLocation(GetWorld(), TeleportSound, GetActorLocation());
				}

				bIsTeleporting = true;

				MyPawn->SetActorRotation(OtherTeleporter->GetActorRotation());
				MyPawn->GetController()->SetControlRotation(MyPawn->GetActorRotation());

				MyPawn->SetActorLocation(OtherTeleporter->GetActorLocation());
			}
		}
	}
}

void ATeleportBox::OnTeleporterExit(AActor* OverlappActor, AActor* OtherActor)
{
	if (OtherActor && OtherActor != this)
	{
		ABallPawn* MyPawn = Cast<ABallPawn>(OtherActor);

		if (MyPawn && OtherTeleporter && !bIsTeleporting)
		{
			if (PawnLook)
			{
				// Get the rotation from the PawnLook arrow
				FRotator ExitRotation = PawnLook->GetComponentRotation();

				if (MyPawn->BallMesh)
				{
					// Stop any physics rotation and set the desired rotation
					MyPawn->BallMesh->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
					MyPawn->BallMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
					MyPawn->BallMesh->SetWorldRotation(ExitRotation);
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("BallMesh is null!"));
				}

				if (AController* Controller = MyPawn->GetController())
				{
					Controller->SetControlRotation(ExitRotation);
				}
			}
			else
			{
				// Log if PawnLook is null
				UE_LOG(LogTemp, Warning, TEXT("PawnLook is null!"));
			}

			OtherTeleporter->bIsTeleporting = false;
		}
	}
}

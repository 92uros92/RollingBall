// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "CoinPickup.h"
#include "BallPawn.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Kismet/GameplayStatics.h"




ACoinPickup::ACoinPickup()
{
	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = SceneComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetupAttachment(SceneComp);
	SphereComp->SetGenerateOverlapEvents(true);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	CoinMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoinMeshComp"));
	CoinMeshComp->SetupAttachment(SphereComp);
	CoinMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CoinMeshComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	CoinMeshComp->SetGenerateOverlapEvents(false);

	RotatingMovmentComp = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovmentComp"));
	RotatingMovmentComp->RotationRate = FRotator(0.0f, 180.0f, 0.0f);
}

void ACoinPickup::BeginPlay()
{
	Super::BeginPlay();
	
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ACoinPickup::OnSphereOverlap);
}

void ACoinPickup::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent,	AActor* OtherActor,	UPrimitiveComponent* OtherComp,	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABallPawn* BallPawn = Cast<ABallPawn>(OtherActor);

	if (BallPawn)
	{
		if (PickupSound)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupSound, GetActorLocation());
		}

		BallPawn->CountCoin();
		//UE_LOG(LogTemp, Warning, TEXT("Coin has been pick up."));

		Destroy();
	}
}
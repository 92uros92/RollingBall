// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "RB_BreakablePlatform.h"
#include "BallPawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"




ARB_BreakablePlatform::ARB_BreakablePlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	RootComponent = BoxCollider;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	PlatformMesh->SetupAttachment(BoxCollider);

}

void ARB_BreakablePlatform::BeginPlay()
{
	Super::BeginPlay();
	
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ARB_BreakablePlatform::OnOverlapBegin);
	BoxCollider->OnComponentEndOverlap.AddDynamic(this, &ARB_BreakablePlatform::OnEndOverlap);
}

void ARB_BreakablePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARB_BreakablePlatform::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABallPawn* BallPawn = Cast<ABallPawn>(OtherActor);

	if (BallPawn)
	{
		GetWorld()->GetTimerManager().SetTimer(BreakTimer, this, &ARB_BreakablePlatform::BreakPlatform, 2.5f, true);

		UE_LOG(LogTemp, Warning, TEXT("Hurry up!! It will break!!"));
	}

}

void ARB_BreakablePlatform::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ABallPawn* BallPawn = Cast<ABallPawn>(OtherActor);

	if (BallPawn)
	{
		GetWorld()->GetTimerManager().SetTimer(AppearTimer, this, &ARB_BreakablePlatform::AppearPlatform, 2.5f, true);
	}
}

void ARB_BreakablePlatform::BreakPlatform()
{
	PlatformMesh->SetVisibility(false);
	PlatformMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (BreakTimer.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(BreakTimer);
	}
}

void ARB_BreakablePlatform::AppearPlatform()
{
	PlatformMesh->SetVisibility(true);
	PlatformMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	if (AppearTimer.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(AppearTimer);
	}
}


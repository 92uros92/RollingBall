// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "RB_BreakablePlatform.h"
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

	bIsPlatformFractured = false;
}

void ARB_BreakablePlatform::BeginPlay()
{
	Super::BeginPlay();
	
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ARB_BreakablePlatform::OnOverlapBegin);

}

void ARB_BreakablePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARB_BreakablePlatform::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && !bIsPlatformFractured)
	{
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ARB_BreakablePlatform::BreakPlatform, 2.5f, false);

		UE_LOG(LogTemp, Warning, TEXT("Hurry up!! It will break!!"));
	}

}

void ARB_BreakablePlatform::BreakPlatform()
{
	if (bIsPlatformFractured) return;

	bIsPlatformFractured = true;

	PlatformMesh->SetVisibility(false);
	PlatformMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FTimerHandle AppearHandle;
	GetWorld()->GetTimerManager().SetTimer(AppearHandle, this, &ARB_BreakablePlatform::AppearPlatform, 2.5f, false);
}

void ARB_BreakablePlatform::AppearPlatform()
{
	bIsPlatformFractured = false;

	PlatformMesh->SetVisibility(true);
	PlatformMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}


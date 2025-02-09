// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "BallPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Components/PrimitiveComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "InputActionValue.h"



ABallPawn::ABallPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
	BallMesh->SetSimulatePhysics(true);
	BallMesh->SetCollisionResponseToAllChannels(ECR_Block);
	BallMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SetRootComponent(BallMesh);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));
	SpringArm->TargetArmLength = 350.0f;
	SpringArm->bEnableCameraLag = false;
	SpringArm->CameraLagSpeed = 5.0f;
	SpringArm->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->bUsePawnControlRotation = false;
	CameraComp->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void ABallPawn::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(BPMappingContext, 0);
		}
	}
}

void ABallPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABallPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ABallPawn::MovePawn);
		EnhancedInputComponent->BindAction(MouseAction, ETriggerEvent::Triggered, this, &ABallPawn::MouseMovement);
	}
}

void ABallPawn::MovePawn(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();

	FVector MovementVector = InputValue.X * CameraComp->GetForwardVector() + InputValue.Y * CameraComp->GetRightVector();
	
	BallMesh->AddForce(MovementVector);
	//UE_LOG(LogTemp, Warning, TEXT("Pawn is moving!!"));
}

void ABallPawn::MouseMovement(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	SpringArm->AddLocalRotation(FRotator(MovementVector.Y, MovementVector.X, 0));
	FRotator SpringArmRotation = SpringArm->GetRelativeRotation();
	SpringArm->SetRelativeRotation(FRotator(SpringArmRotation.Pitch, SpringArmRotation.Yaw, 0));
}


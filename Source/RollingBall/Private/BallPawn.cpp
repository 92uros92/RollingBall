// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "BallPawn.h"
#include "RollingBallGameMode.h"
#include "UI/RollingBallHUD.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/GameplayStatics.h"

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

	//RotationSpeed = 10.0f;
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

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = true;
		PlayerController->bEnableMouseOverEvents = true;

		FInputModeGameAndUI InputData;
		InputData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputData.SetHideCursorDuringCapture(false);

		PlayerController->SetInputMode(InputData);
	}
}

void ABallPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//
	//
	//	1.) Add sound and particles
	//	2.) Measure your time
	//	3.) Add more levels
	//
	//
	//

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

	//AddControllerYawInput(MovementVector * RotationSpeed * GetWorld()->GetDeltaSeconds());
	//AddControllerPitchInput(MovementVector * RotationSpeed * GetWorld()->GetDeltaSeconds());
}

void ABallPawn::CountCoin()
{
	RollingBallGM = Cast<ARollingBallGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (RollingBallGM)
	{
		RollingBallGM->CountCoin();
	}

}


// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BallPawn.generated.h"



UCLASS()
class ROLLINGBALL_API ABallPawn : public APawn
{
	GENERATED_BODY()

public:

	ABallPawn();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void CountCoin();


protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* BallMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* BPMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MouseAction;

	// ******** FUNCTIONS ******** //

	virtual void BeginPlay() override;

	UFUNCTION()
	void MovePawn(const FInputActionValue& Value);

	UFUNCTION()
	void MouseMovement(const FInputActionValue& Value);

private:	

	UPROPERTY(VisibleInstanceOnly)
	class ARollingBallGameMode* RollingBallGM;
};

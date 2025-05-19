// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "TankCharacter.generated.h"


class UTextRenderComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class TANKMECHANICS_API ATankCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

	// Sets default values for this character's properties
	ATankCharacter();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	UInputMappingContext* InputMapping;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	UInputAction* IA_TankMove;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	UInputAction* IA_TankTurn;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	UInputAction* IA_TurretRotate;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	UInputAction* IA_TurretFire;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxForwardSpeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ForwardAcceleration;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float TankRotateSpeed;
	float CurrentForwardSpeed = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float TurretRotateSpeed;
	float CurrentTurretAngle = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void UpdateCharacter();
	void MoveForward(const FInputActionValue& Value);
	void ResetAcceleration();
	void TankTurn(const FInputActionValue& Value);
	void TurretRotate(const FInputActionValue& Value);
	void TurretFire();
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
};
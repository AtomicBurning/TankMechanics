// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"

#include "TankAnimInstance.h"
#include "SoundManagerComponent.h"

#include "TankCharacter.generated.h"


class UTextRenderComponent;
class UInputMappingContext;
class UInputAction;

class USoundManagerComponent;

class UTankIdle;
class UTankDrive;
class UTankNeutralState;

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
	float TurretYaw = 0;

	bool CanFire = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(const FInputActionValue& Value);
	void TankStop();
	void TankTurn(const FInputActionValue& Value);
	void TurnStop();
	void TurretRotate(const FInputActionValue& Value);
	void TurretFire();
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//State Machine Stuff
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = States)
	class UTankState* TankIdleState;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = States)
	class UTankState* TankDriveState;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = States)
	class UTankState* TankNeutralSteerState;

	void SetState(UTankState* NewState);
	UTankState* GetCurrentState() const;

private:
	class UTankState* CurrentState;

//SFXs
public:
	UPROPERTY()
	USoundManagerComponent* SoundManager;

	UPROPERTY(EditDefaultsOnly, Category = "SFX")
	USoundBase* FireSFX;
	float FireTime;

	UPROPERTY(EditDefaultsOnly, Category = "SFX")
	USoundBase* ReloadSFX;
	float ReloadTime;
};
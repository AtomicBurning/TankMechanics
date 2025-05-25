// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TankCharacter.h"
#include "TankState.generated.h"

class ATankCharacter;

UCLASS(Abstract, Blueprintable)
class TANKMECHANICS_API UTankState : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	ATankCharacter* Tank;

public:
	void SetTank(ATankCharacter* TankOwner);

	virtual void EnterState();
	virtual void ExitState();

	virtual void MoveForward(float Value);
	virtual void TankStop();
	virtual void TankTurn(float Value);
	virtual void TurnStop();

	virtual void UpdateState(float DeltaTime);
	virtual void HandleState();

	bool IsMoving = false;
	bool IsTurning = false;
};

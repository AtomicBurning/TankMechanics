// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankState.h"
#include "TankDrive.generated.h"

UCLASS()
class TANKMECHANICS_API UTankDrive : public UTankState
{
	GENERATED_BODY()

public:
	virtual void EnterState() override;

	virtual void MoveForward(float Value) override;
	virtual void TankStop() override;
	virtual void TankTurn(float Value) override;
	virtual void TurnStop() override;

	virtual void HandleState() override;
};

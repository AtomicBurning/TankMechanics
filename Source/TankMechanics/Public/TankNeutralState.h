// Fill out your copyright notice in the Description page of Project Settings.
//This should be named TankNeutralSteer - incase I forget to rename it

#pragma once

#include "CoreMinimal.h"
#include "TankState.h"
#include "TankNeutralState.generated.h"

UCLASS()
class TANKMECHANICS_API UTankNeutralState : public UTankState
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

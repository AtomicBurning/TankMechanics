// Fill out your copyright notice in the Description page of Project Settings.
//Wait on second thought not worth.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TankCharacter.h"
#include "CannonState.generated.h"

class ATankCharacter;

UCLASS(Abstract, Blueprintable)
class TANKMECHANICS_API UCannonState : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	ATankCharacter* Tank;

public:
	void SetTank(ATankCharacter* TankOwner);

	virtual void EnterState();
	virtual void ExitState();

	virtual void Fire();

	virtual void UpdateState(float DeltaTime);
	virtual void HandleState();

	float ReloadTimer = 0;
};


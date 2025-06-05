// Fill out your copyright notice in the Description page of Project Settings.


#include "CannonState.h"

void UCannonState::SetTank(ATankCharacter* TankOwner)
{
	Tank = TankOwner;
}

void UCannonState::EnterState() {}
void UCannonState::ExitState() {}

void UCannonState::Fire() {}

void UCannonState::UpdateState(float DeltaTime) {}
void UCannonState::HandleState() {}


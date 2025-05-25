// Fill out your copyright notice in the Description page of Project Settings.


#include "TankState.h"

void UTankState::SetTank(ATankCharacter* TankOwner)
{
	Tank = TankOwner;
}

void UTankState::EnterState() {}
void UTankState::ExitState() {}

void UTankState::MoveForward(float Value) {}
void UTankState::TankStop() {}
void UTankState::TankTurn(float Value) {}
void UTankState::TurnStop() {}

void UTankState::UpdateState(float DeltaTime) {}
void UTankState::HandleState() {}

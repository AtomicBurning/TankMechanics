// Fill out your copyright notice in the Description page of Project Settings.


#include "TankIdle.h"

void UTankIdle::EnterState()
{
    IsMoving = false;
    IsTurning = false;

    UE_LOG(LogTemp, Warning, TEXT("Idle"));
}

void UTankIdle::MoveForward(float Value)
{
    float BaseSpeed = Value;

    if (BaseSpeed != 0)
    {
        IsMoving = true;
    }
}

void UTankIdle::TankTurn(float Value)
{
    float TurnValue = Value;
    if (TurnValue != 0.0f)
    {
        IsTurning = true;
    }
}

void UTankIdle::HandleState()
{
    if (IsTurning && !IsMoving)
        Tank->SetState(Tank->NeutralSteerState);

    if (IsMoving)
        Tank->SetState(Tank->DriveState);
}

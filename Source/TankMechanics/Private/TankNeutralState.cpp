// Fill out your copyright notice in the Description page of Project Settings.
//This should be named TankNeutralSteer - incase I forget to rename it

#include "TankNeutralState.h"

void UTankNeutralState::EnterState()
{
    IsMoving = false;
    IsTurning = true;

    UE_LOG(LogTemp, Warning, TEXT("NeutralSteer"));
}

void UTankNeutralState::MoveForward(float Value)
{
    IsMoving = true;
}

void UTankNeutralState::TankStop()
{
    Tank->CurrentForwardSpeed = 0;
    IsMoving = false;
}

void UTankNeutralState::TankTurn(float Value)
{
    float TurnValue = Value * 0.2f;

    IsTurning = true;
    // Get the controller's rotation
    FRotator NewRotation = Tank->GetControlRotation();
    NewRotation.Yaw += TurnValue * Tank->TankRotateSpeed * GetWorld()->GetDeltaSeconds();

    // Set the new rotation
    Tank->GetController()->SetControlRotation(NewRotation);
}

void UTankNeutralState::TurnStop()
{
    IsTurning = false;
}

void UTankNeutralState::HandleState()
{
    if (IsMoving)
        Tank->SetState(Tank->TankDriveState);
    if (!IsTurning && !IsMoving)
        Tank->SetState(Tank->TankIdleState);
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "TankDrive.h"

void UTankDrive::EnterState()
{
    IsMoving = true;

    UE_LOG(LogTemp, Warning, TEXT("Drive"));
}

void UTankDrive::MoveForward(float Value)
{
    IsMoving = true;

    float BaseSpeed = Value;

    if (BaseSpeed > 0)
    {
        Tank->CurrentForwardSpeed += FMath::Clamp(FMath::Abs(BaseSpeed) * Tank->ForwardAcceleration * GetWorld()->GetDeltaSeconds(), -Tank->MaxForwardSpeed, Tank->MaxForwardSpeed);
    }
    else
    {
        Tank->CurrentForwardSpeed += FMath::Clamp(FMath::Abs(BaseSpeed) * (Tank->ForwardAcceleration / 5) * GetWorld()->GetDeltaSeconds(), -Tank->MaxForwardSpeed / 5, Tank->MaxForwardSpeed / 5);
    }

    Tank->GetCharacterMovement()->MaxWalkSpeed = Tank->CurrentForwardSpeed;
    Tank->AddMovementInput(Tank->GetActorForwardVector(), BaseSpeed);
}

void UTankDrive::TankStop()
{
    Tank->CurrentForwardSpeed = 0;
    IsMoving = false;
}

void UTankDrive::TankTurn(float Value)
{
    float TurnValue = Value * FMath::Clamp(Tank->CurrentForwardSpeed / 200, 1, 5);

    IsTurning = true;
    // Get the controller's rotation
    FRotator NewRotation = Tank->GetControlRotation();

    NewRotation.Yaw += TurnValue * Tank->TankRotateSpeed * GetWorld()->GetDeltaSeconds();

    // Set the new rotation
    Tank->GetController()->SetControlRotation(NewRotation);
}

void UTankDrive::TurnStop()
{
    IsTurning = false;
}

void UTankDrive::HandleState()
{
    if (!IsMoving)
    {
        if (!IsTurning)
            Tank->SetState(Tank->TankIdleState);
        else
            Tank->SetState(Tank->TankNeutralSteerState);
    }
}
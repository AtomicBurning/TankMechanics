// Fill out your copyright notice in the Description page of Project Settings.


#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "TankIdle.h"
#include "TankDrive.h"
#include "TankNeutralState.h"

#include "TankCharacter.h"

// Sets default values
ATankCharacter::ATankCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    GetCharacterMovement();

    IdleState = CreateDefaultSubobject<UTankIdle>(TEXT("IdleState"));
    DriveState = CreateDefaultSubobject<UTankDrive>(TEXT("DriveState"));
    NeutralSteerState = CreateDefaultSubobject<UTankNeutralState>(TEXT("NeutralSteerState"));
}

// Called every frame
void ATankCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    CurrentState->UpdateState(DeltaTime);
    CurrentState->HandleState();
}

void ATankCharacter::BeginPlay()
{
    Super::BeginPlay();
    IdleState->SetTank(this);
    DriveState->SetTank(this);
    NeutralSteerState->SetTank(this);
    SetState(IdleState);
}

void ATankCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Cast PlayerInputComponent to UEnhancedInputComponent
    if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // Bind the MoveForward action
        if (IA_TankMove)
        {
            Input->BindAction(IA_TankMove, ETriggerEvent::Triggered, this, &ATankCharacter::MoveForward);
            Input->BindAction(IA_TankMove, ETriggerEvent::Completed, this, &ATankCharacter::TankStop);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("IA_Move is not initialized!"));
        }

        // Bind the TankTurn action
        if (IA_TankTurn)
        {
            Input->BindAction(IA_TankTurn, ETriggerEvent::Triggered, this, &ATankCharacter::TankTurn);
            Input->BindAction(IA_TankTurn, ETriggerEvent::Completed, this, &ATankCharacter::TurnStop);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("IA_Move is not initialized!"));
        }

        // Bind the TurretRotate action
        if (IA_TurretRotate)
        {
            Input->BindAction(IA_TurretRotate, ETriggerEvent::Triggered, this, &ATankCharacter::TurretRotate);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("IA_TurretRotate is not initialized!"));
        }

        // Bind the TurretFire action
        if (IA_TurretFire)
        {
            Input->BindAction(IA_TurretFire, ETriggerEvent::Triggered, this, &ATankCharacter::TurretFire);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("IA_TurretFire is not initialized!"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to cast PlayerInputComponent to UEnhancedInputComponent"));
    }

    // Set up the Enhanced Input Subsystem
    if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->ClearAllMappings();
            if (InputMapping)
            {
                Subsystem->AddMappingContext(InputMapping, 0);
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("InputMapping is not initialized!"));
            }
        }
    }
}

void ATankCharacter::MoveForward(const FInputActionValue& Value)
{
    if (CurrentState)
        CurrentState->MoveForward(Value.Get<float>());
}

void ATankCharacter::TankStop()
{
    if (CurrentState)
        CurrentState->TankStop();
}

void ATankCharacter::TankTurn(const FInputActionValue& Value)
{
    if (CurrentState)
        CurrentState->TankTurn(Value.Get<float>());
}

void ATankCharacter::TurnStop()
{
    if (CurrentState)
        CurrentState->TurnStop();
}

void ATankCharacter::TurretRotate(const FInputActionValue& Value)
{

}

void ATankCharacter::TurretFire()
{

}

//State Machine Stuff
void ATankCharacter::SetState(UTankState* NewState)
{
    CurrentState = NewState;
    CurrentState->EnterState();
}

UTankState* ATankCharacter::GetCurrentState() const
{
    return CurrentState;
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "TankCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
ATankCharacter::ATankCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    GetCharacterMovement();
}

// Called every frame
void ATankCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    UpdateCharacter();
}

void ATankCharacter::BeginPlay()
{
    Super::BeginPlay();
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
            Input->BindAction(IA_TankMove, ETriggerEvent::Completed, this, &ATankCharacter::ResetAcceleration);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("IA_Move is not initialized!"));
        }

        // Bind the TankTurn action
        if (IA_TankTurn)
        {
            Input->BindAction(IA_TankTurn, ETriggerEvent::Triggered, this, &ATankCharacter::TankTurn);
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
    // Apply the input to the character motion

    float BaseSpeed = Value.Get<float>();

    if (BaseSpeed > 0)
    {
        if (CurrentForwardSpeed < MaxForwardSpeed)
        {
            CurrentForwardSpeed += FMath::Abs(BaseSpeed) * ForwardAcceleration * GetWorld()->GetDeltaSeconds();
        }
    }
    else
    {
        if (CurrentForwardSpeed < MaxForwardSpeed / 5)
        {
            CurrentForwardSpeed += FMath::Abs(BaseSpeed) * ForwardAcceleration / 5 * GetWorld()->GetDeltaSeconds();
        }
    }

    GetCharacterMovement()->MaxWalkSpeed = CurrentForwardSpeed;
    AddMovementInput(GetActorForwardVector(), BaseSpeed);
    UE_LOG(LogTemp, Warning, TEXT("Moving with value: %f"), CurrentForwardSpeed);
}

void ATankCharacter::ResetAcceleration()
{
    CurrentForwardSpeed = 0;
}

void ATankCharacter::TankTurn(const FInputActionValue& Value)
{
    float TurnValue = Value.Get<float>();
    if (TurnValue != 0.0f)
    {
        // Get the controller's rotation
        FRotator NewRotation = GetControlRotation();
        NewRotation.Yaw += TurnValue * TankRotateSpeed * GetWorld()->GetDeltaSeconds();

        // Set the new rotation
        GetController()->SetControlRotation(NewRotation);

        //UE_LOG(LogTemp, Warning, TEXT("Turning with value: %f"), TurnValue);
    }
}

void ATankCharacter::TurretRotate(const FInputActionValue& Value)
{

}

void ATankCharacter::TurretFire()
{

}

void ATankCharacter::UpdateCharacter()
{
    const FVector PlayerVelocity = GetVelocity();
    float TravelDirection = PlayerVelocity.X;
}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"
#include "SoundManagerComponent.generated.h"

UENUM(BlueprintType)
enum class ETankSoundChannel : uint8
{
    Chassis,
    Turret,
    Cannon,
    Ambient,
};

UCLASS(ClassGroup = (Audio), meta = (BlueprintSpawnableComponent))
class TANKMECHANICS_API USoundManagerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USoundManagerComponent();

    UFUNCTION(BlueprintCallable)
    void PlaySound(ETankSoundChannel Channel, USoundBase* Sound);

    UFUNCTION(BlueprintCallable)
    void StopSound(ETankSoundChannel Channel);

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    TMap<ETankSoundChannel, UAudioComponent*> ChannelMap;

    UAudioComponent* GetOrCreateAudioComponent(ETankSoundChannel Channel);
};

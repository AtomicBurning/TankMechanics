// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundManagerComponent.h"

USoundManagerComponent::USoundManagerComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USoundManagerComponent::BeginPlay()
{
    Super::BeginPlay();
}

UAudioComponent* USoundManagerComponent::GetOrCreateAudioComponent(ETankSoundChannel Channel)
{
    if (UAudioComponent** Found = ChannelMap.Find(Channel))
    {
        return *Found;
    }

    UAudioComponent* NewAudio = NewObject<UAudioComponent>(this);
    NewAudio->RegisterComponent();
    NewAudio->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
    ChannelMap.Add(Channel, NewAudio);
    return NewAudio;
}

void USoundManagerComponent::PlaySound(ETankSoundChannel Channel, USoundBase* Sound)
{
    if (!Sound) return;

    UAudioComponent* AudioComp = GetOrCreateAudioComponent(Channel);
    if (AudioComp)
    {
        AudioComp->SetSound(Sound);
        AudioComp->bIsUISound = false;
        AudioComp->bAutoActivate = false;
        AudioComp->Play();
    }
}

void USoundManagerComponent::StopSound(ETankSoundChannel Channel)
{
    if (UAudioComponent** Found = ChannelMap.Find(Channel))
    {
        if (UAudioComponent* Comp = *Found)
        {
            Comp->Stop();
        }
    }
}



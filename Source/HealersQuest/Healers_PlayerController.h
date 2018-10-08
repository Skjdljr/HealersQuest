// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Healers_PlayerController.generated.h"

class UAudioComponent;

/**
 * 
 */
UCLASS()
class HEALERSQUEST_API AHealers_PlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    
    AHealers_PlayerController();

    // Override BeginPlay()
    virtual void BeginPlay() override;

    UPROPERTY(Config, BlueprintReadWrite, VisibleAnywhere, Meta = (ClampMin = 0.0, ClampMax = 1.0), Category = "Audio")
    float MusicVolumeScalar;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Audio")
    UAudioComponent* MusicComponent;

    UFUNCTION(BlueprintCallable, Category = "Healers|PlayerController|Music")
    void PlayMusic(USoundBase* Music, float FadeInDuration);

    UFUNCTION(BlueprintCallable, Category = "Healers|PlayerController|Music")
    void StopMusic(float FadeOutDuration);

    UFUNCTION(BlueprintCallable, Category = "Healers|PlayerController|Music")
    void SetMusicVolume(float MusicVolume);
};
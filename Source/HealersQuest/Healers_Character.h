// Fill out your copyright notice in the Description page of Project Settings.

/////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Healers_AbilitySystemComponent.h"

#include "Healers_Character.generated.h"

/////////////////////////////////////////////////////////////////////////////////////////////////

UCLASS()
class HEALERSQUEST_API AHealers_Character : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    AHealers_Character();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:	
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    /*
    * Ability System Component
    */
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Character")
    UHealers_AbilitySystemComponent* AbilityComponent;
};

// Fill out your copyright notice in the Description page of Project Settings.

/////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "CoreMinimal.h"

#include "HealersQuest.h"
#include "Healers_Spell.h"
#include "Healers_CharacterAttributes.generated.h"

/////////////////////////////////////////////////////////////////////////////////////////////////

#pragma region FDamageResistance

/**
* FDamageResistance : Damage Resistance structure.
*
*/
USTRUCT(BlueprintType, Meta = (ScriptName = "Damage Resistance Structure"))
struct FDamageResistance
{
    GENERATED_BODY()

    FDamageResistance();

    /* DamageResistance Type */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DamageResistance")
    EDamageResistance DamageType;

    /* Flat DamageResistance Percent Value */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DamageResistance")
    float DamageResistancePercentValue;

    /* Flat DamageResistance Value */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DamageResistance")
    float DamageResistanceValue;
};

#pragma endregion FDamageResistance


#pragma region FCharacterAttributes

/**
* FCharacterAttributes : Core structure for Character Data. Used by Race, Profession, and Character data structures.
*
*/
USTRUCT(BlueprintType, Blueprintable)
struct FCharacterAttributes
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "CharacterAttributes")
    float Health;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterAttributes")
    float HealthMax;

    UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "CharacterAttributes")
    float Mana;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterAttributes")
    float ManaMax;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterAttributes")
    float ManaRegenerationPerSecond;

    UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "CharacterAttributes")
    float Initiative;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterAttributes")
    float InitiativePerSecond;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterAttributes")
    float AttackAccuracy;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterAttributes")
    float AttackPower;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterAttributes")
    float MagicAccuracy;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterAttributes")
    float MagicPower;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterAttributes")
    float CriticalDamageChance;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterAttributes")
    float CriticalDamageValue;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterAttributes")
    float EvasionValue;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterAttributes")
    float ArmorValue;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterAttributes")
    float LuckValue;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterAttributes")
    TArray<FDamageResistance> Resistances;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterAttributes")
    TArray<TSubclassOf<AHealers_Spell>> Abilities;

    FCharacterAttributes();
};

#pragma endregion FCharacterAttributes
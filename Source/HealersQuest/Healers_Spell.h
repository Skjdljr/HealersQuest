// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Healers_Spell.generated.h"

class UHealers_SpellComponent;
class UHealers_SpellTargetingComponent;
class UHealers_SpellPrerequisiteComponent;

/**
 * The Healers Spell is intended to be a blueprintable object where each blueprint can configure their
 * own spell components that define the function of the spell.
 */
UCLASS()
class HEALERSQUEST_API AHealers_Spell : public AActor
{
    GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Healers")
	TArray<UHealers_SpellComponent*> SpellComponents;

	/* Component that's responsible for specifying which actors this spell will affect. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Healers")
	UHealers_SpellTargetingComponent* TargetComponent;

	/* List of components that determines if this spell can be casted on target or not. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Healers")
	TArray<UHealers_SpellPrerequisiteComponent*> Prerequisites;

	/* Human readable name of this spell (meant to be displayed on UI for example). */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Healers")
	FText SpellName;

	AHealers_Spell(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay () override;
	virtual void Destroyed () override;
	virtual void Tick (float deltaSec) override;

	/* Returns true if all requirements are met, and the user is allowed to choose this spell.
	Useful for conditions before a target is selected (eg:  is it on cooldown?  Do you have enough mana?) */
	UFUNCTION(BlueprintCallable, Category="Healers")
	virtual bool CanCastSpell(APawn* caster) const;

	/* Returns true if all requirements are met, and the user is allowed to cast the spell on specified actors.
	This is useful if you want to deny the spell cast because the user has chosen an invalid target. */
	UFUNCTION(BlueprintCallable, Category="Healers")
	virtual bool CanCastSpellOnTargets(APawn* caster, const TArray<AActor*>& targets) const;

	UFUNCTION(BlueprintCallable, Category="Healers")
	/* Initializes the spell components and executes the spell sequence. */
	virtual void CastSpell(APawn* caster, const TArray<AActor*>& targets);
};
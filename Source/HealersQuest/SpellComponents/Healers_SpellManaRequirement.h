// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Healers_SpellPrerequisiteComponent.h"
#include "Healers_SpellManaRequirement.generated.h"

class AHealers_Spell;

UCLASS(Blueprintable, BlueprintType, Category="Healers", meta=(BlueprintSpawnableComponent))
class HEALERSQUEST_API UHealers_SpellManaRequirement : public UHealers_SpellPrerequisiteComponent
{
    GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Healers")
	float ManaCost;

    UHealers_SpellManaRequirement(const FObjectInitializer& ObjectInitializer);

	virtual bool CanCastSpell(APawn* caster) const override;
	virtual void SpellExecuted(APawn* caster) override;
};
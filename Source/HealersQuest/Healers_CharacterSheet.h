// Fill out your copyright notice in the Description page of Project Settings.

/////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Info.h"
#include "Engine/DataTable.h"

#include "HealersQuest.h"
#include "Healers_Spell.h"
#include "Healers_CharacterAttributes.h"

#include "Healers_CharacterSheet.generated.h"

/////////////////////////////////////////////////////////////////////////////////////////////////

USTRUCT(BlueprintType, Blueprintable)
struct FProfessionIconSet : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Profession Icon Set")
    ECharacterProfession Profession;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Profession Icon Set")
    UTexture2D* Icon;
};

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

/**
* FCharacterRace : Character Race Definition. Design-time structure stored in DataTable. 
*
*/
USTRUCT(BlueprintType, Blueprintable)
struct FCharacterRaceDefinition : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterRace")
    int32 Level;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterRace")
    FString RaceName;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterRace")
    FCharacterAttributes Attributes;
};

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

/**
* FCharacterRaceLibrary : Character Race Library. Define DataTables used by each Race.
*
*/
USTRUCT(BlueprintType, Blueprintable)
struct FCharacterRaceLibrary : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Profession")
    ECharacterRace Race;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Profession")
    UDataTable* DataTable;
};

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

/**
* FCharacterProfessionDefinition : Character Profession Definition. Design-time structure stored in DataTable.
*
*/
USTRUCT(BlueprintType, Blueprintable)
struct FCharacterProfessionDefinition : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Profession")
    int32 Level;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Profession")
    FString ProfessionName;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Profession")
    FCharacterAttributes Attributes;
};

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

/**
* FCharacterProfessionLibrary : Character Profession Library. Define DataTables used by each Profession.
*
*/
USTRUCT(BlueprintType, Blueprintable)
struct FCharacterProfessionLibrary : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Profession")
    ECharacterProfession Profession;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Profession")
    UDataTable* DataTable;
};

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

/**
* Obsolete - Only needed for Multiclass support.
* FCharacterProfessionLevel : Character Profession-Level. BP-Exposed structure storing set of Profession and Level.
*
*/
//USTRUCT(BlueprintType, Blueprintable)
//struct FCharacterProfessionLevel
//{
//    GENERATED_BODY()
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Profession")
//    ECharacterProfession Profession;
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Profession")
//    int32 Level;
//};

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

/**
* FCharacterSheet : Character Sheet. Design-time structure stored in DataTable.
*
*/
USTRUCT(BlueprintType, Blueprintable)
struct FCharacterSheet : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "CharacterSheet")
    FString CharacterName;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "CharacterSheet")
    UTexture2D* CharacterIcon;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "CharacterSheet")
    int32 Level;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "CharacterSheet")
    float Experience;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "CharacterSheet")
    ECharacterRace Race;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "CharacterSheet")
    ECharacterProfession Profession;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "CharacterSheet")
    FCharacterAttributes Attributes;

    // @! TODO: 
    // FCharacterInventory Inventory;
};

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////
// Delegates

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSpellEffectChanged, AHealers_Spell*, spell, bool, isStackable);

/**
* AHealers_CharacterSheet : Character Sheet Actor. Run-time instance of a CharacterSheet.
*
*/
UCLASS(Blueprintable, BlueprintType, NotPlaceable)
class HEALERSQUEST_API AHealers_CharacterSheet : public AInfo
{
    GENERATED_BODY()

public:

    AHealers_CharacterSheet();

    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category = "CharacterSheet")
    void InitializeCharacter();

    UFUNCTION()
    void InitializeRaceAttributes(UDataTable* CharacterRaceDataTable);
    
    UFUNCTION()
    void InitializeProfessionAttributes(UDataTable* CharacterProfessionDataTable);
    
    UFUNCTION()
    void AddAttributes(const FCharacterAttributes& InAttributes);

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "CharacterSheet")
    FCharacterSheet CharacterSheet;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterSheet")
    AHealers_Spell* CurrentSelectedSpell;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "CharacterSheet")
    bool bIsPlayer;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterSheet")
    TArray<AHealers_Spell*> ActiveEffects;

    UPROPERTY(BlueprintAssignable, Category = "CharacterSheet")
    FOnSpellEffectChanged OnSpellEffectAdded;

    /**
    * Getter and Setters
    */

    // Name
    UFUNCTION(BlueprintPure, BlueprintCallable, meta = (Keywords = "Character Name"), Category = "CharacterSheet")
    FString GetCharacterName() const { return CharacterSheet.CharacterName; }

    UFUNCTION(BlueprintCallable, meta = (Keywords = "Character Name"), Category = "CharacterSheet")
    void SetCharacterName(const FString& InName) { CharacterSheet.CharacterName = InName; }

    // Race
    UFUNCTION(BlueprintPure, BlueprintCallable, meta = (Keywords = "Character Race"), Category = "CharacterSheet")
    ECharacterRace GetRace() const { return CharacterSheet.Race; }

    // Profession
    UFUNCTION(BlueprintPure, BlueprintCallable, meta = (Keywords = "Character Profession"), Category = "CharacterSheet")
    ECharacterProfession GetProfession() const { return CharacterSheet.Profession; }

    // Attributes
    UFUNCTION(BlueprintPure, BlueprintCallable, meta = (Keywords = "Character Attributes"), Category = "CharacterSheet")
    FCharacterAttributes& GetAttributes() { return CharacterSheet.Attributes; }

    // Level
    UFUNCTION(BlueprintPure, BlueprintCallable, meta = (Keywords = "Character Level"), Category = "CharacterSheet")
    int32 GetCharacterLevel() const { return CharacterSheet.Level; }

    UFUNCTION(BlueprintCallable, meta = (Keywords = "Character Level"), Category = "CharacterSheet")
    void SetLevel(const int32 InLevel) { CharacterSheet.Level = InLevel; }

    // Experience
    UFUNCTION(BlueprintPure, BlueprintCallable, meta = (Keywords = "Character Experience"), Category = "CharacterSheet")
    float GetExperience() const { return CharacterSheet.Experience; }

    UFUNCTION(BlueprintCallable, meta = (Keywords = "Character Experience"), Category = "CharacterSheet")
    void SetExperience(const float InExperience) { CharacterSheet.Experience = InExperience; }

    // Initiative
    UFUNCTION(BlueprintPure, BlueprintCallable, meta = (Keywords = "Character Initiative"), Category = "CharacterSheet")
    float GetInitiative() const { return CharacterSheet.Attributes.Initiative; }

    UFUNCTION(BlueprintCallable, meta = (Keywords = "Character Initiative"), Category = "CharacterSheet")
    void SetInitiative(const float InInitiative) { CharacterSheet.Attributes.Initiative = InInitiative; }

    UFUNCTION(BlueprintPure, BlueprintCallable, meta = (Keywords = "Character InitiativePerSecond"), Category = "CharacterSheet")
    float GetInitiativePerSecond() const { return CharacterSheet.Attributes.InitiativePerSecond; }

    UFUNCTION(BlueprintCallable, meta = (Keywords = "Character InitiativePerSecond"), Category = "CharacterSheet")
    void SetInitiativePerSecond(const float InInitiativePerSecond) { CharacterSheet.Attributes.InitiativePerSecond = InInitiativePerSecond; }

    // Health
    UFUNCTION(BlueprintPure, BlueprintCallable, meta = (Keywords = "Character Health"), Category = "CharacterSheet")
    float GetHealth() const { return CharacterSheet.Attributes.Health; }

    UFUNCTION(BlueprintCallable, meta = (Keywords = "Character Health"), Category = "CharacterSheet")
    void SetHealth(const float InHealth) { CharacterSheet.Attributes.Health = InHealth; }

    UFUNCTION(BlueprintPure, BlueprintCallable, meta = (Keywords = "Character HealthMax"), Category = "CharacterSheet")
    float GetHealthMax() const { return CharacterSheet.Attributes.HealthMax; }

    // Mana
    UFUNCTION(BlueprintPure, BlueprintCallable, meta = (Keywords = "Character Mana"), Category = "CharacterSheet")
    float GetMana() const { return CharacterSheet.Attributes.Mana; }

    UFUNCTION(BlueprintCallable, meta = (Keywords = "Character Mana"), Category = "CharacterSheet")
    void SetMana(const float InMana) { CharacterSheet.Attributes.Mana = InMana; }

    UFUNCTION(BlueprintPure, BlueprintCallable, meta = (Keywords = "Character ManaMax"), Category = "CharacterSheet")
    float GetManaMax() const { return CharacterSheet.Attributes.ManaMax; }

    UFUNCTION(BlueprintCallable, meta = (Keywords = "Character Mana"), Category = "CharacterSheet")
    void SetManaMax(const float InManaMax) { CharacterSheet.Attributes.Mana = InManaMax; }

    UFUNCTION(BlueprintPure, BlueprintCallable, meta = (Keywords = "Character ManaRegeneration"), Category = "CharacterSheet")
    float GetManaRegenerationPerSecond() const { return CharacterSheet.Attributes.ManaRegenerationPerSecond; }

    UFUNCTION(BlueprintCallable, meta = (Keywords = "Character Mana"), Category = "CharacterSheet")
    void SetManaRegenerationPerSecond(const float InManaRegenerationPerSecond) { CharacterSheet.Attributes.ManaRegenerationPerSecond = InManaRegenerationPerSecond; }

    // Attack
    UFUNCTION(BlueprintPure, BlueprintCallable, meta = (Keywords = "Character Attack Accuracy"), Category = "CharacterSheet")
    float GetAttackAccuracy() const { return CharacterSheet.Attributes.AttackAccuracy; }

    UFUNCTION(BlueprintCallable, meta = (Keywords = "Character Attack Accuracy"), Category = "CharacterSheet")
    void SetAttackAccuracy(const float InAttackAccuracy) { CharacterSheet.Attributes.AttackAccuracy = InAttackAccuracy; }

    UFUNCTION(BlueprintPure, BlueprintCallable, meta = (Keywords = "Character Attack Power"), Category = "CharacterSheet")
    float GetAttackPower() const { return CharacterSheet.Attributes.AttackPower; }

    UFUNCTION(BlueprintCallable, meta = (Keywords = "Character Attack Power"), Category = "CharacterSheet")
    void SetAttackPower(const float InAttackPower) { CharacterSheet.Attributes.AttackPower = InAttackPower; }

    // Magic
    UFUNCTION(BlueprintPure, BlueprintCallable, meta = (Keywords = "Character Magic Accuracy"), Category = "CharacterSheet")
    float GetMagicAccuracy() const { return CharacterSheet.Attributes.MagicAccuracy; }

    UFUNCTION(BlueprintCallable, meta = (Keywords = "Character Magic Accuracy"), Category = "CharacterSheet")
    void SetMagicAccuracy(const float InMagicAccuracy) { CharacterSheet.Attributes.MagicAccuracy = InMagicAccuracy; }

    UFUNCTION(BlueprintPure, BlueprintCallable, meta = (Keywords = "Character Magic Power"), Category = "CharacterSheet")
    float GetMagicPower() const { return CharacterSheet.Attributes.MagicPower; }

    UFUNCTION(BlueprintCallable, meta = (Keywords = "Character Magic Power"), Category = "CharacterSheet")
    void SetMagicPower(const float InMagicPower) { CharacterSheet.Attributes.MagicPower = InMagicPower; }

    // Critical
    UFUNCTION(BlueprintPure, BlueprintCallable, meta = (Keywords = "Character Critical Damage Chance"), Category = "CharacterSheet")
    float GetCriticalChance() const { return CharacterSheet.Attributes.CriticalDamageChance; }

    UFUNCTION(BlueprintCallable, meta = (Keywords = "Character Critical Damage Chance"), Category = "CharacterSheet")
    void SetCriticalChance(const float InCriticalChance) { CharacterSheet.Attributes.CriticalDamageChance = InCriticalChance; }

    UFUNCTION(BlueprintPure, BlueprintCallable, meta = (Keywords = "Character Critical Damage Power"), Category = "CharacterSheet")
    float GetCriticalPower() const { return CharacterSheet.Attributes.CriticalDamageValue; }

    UFUNCTION(BlueprintCallable, meta = (Keywords = "Character Critical Damage Power"), Category = "CharacterSheet")
    void SetCriticalPower(const float InCriticalPower) { CharacterSheet.Attributes.CriticalDamageValue = InCriticalPower; }

    // Defense
    UFUNCTION(BlueprintPure, BlueprintCallable, meta = (Keywords = "Character Evasion"), Category = "CharacterSheet")
    float GetEvasion() const { return CharacterSheet.Attributes.EvasionValue; }

    UFUNCTION(BlueprintCallable, meta = (Keywords = "Character Evasion"), Category = "CharacterSheet")
    void SetEvasion(const float InEvasion) { CharacterSheet.Attributes.EvasionValue = InEvasion; }

    UFUNCTION(BlueprintPure, BlueprintCallable, meta = (Keywords = "Character Armor"), Category = "CharacterSheet")
    float GetArmor() const { return CharacterSheet.Attributes.ArmorValue; }

    UFUNCTION(BlueprintCallable, meta = (Keywords = "Character Armor"), Category = "CharacterSheet")
    void SetArmor(const float InArmor) { CharacterSheet.Attributes.ArmorValue = InArmor; }

    // Luck
    UFUNCTION(BlueprintPure, BlueprintCallable, meta = (Keywords = "Character Luck"), Category = "CharacterSheet")
    float GetLuck() const { return CharacterSheet.Attributes.LuckValue; }

    UFUNCTION(BlueprintCallable, meta = (Keywords = "Character Luck"), Category = "CharacterSheet")
    void SetLuck(const float InLuck) { CharacterSheet.Attributes.LuckValue = InLuck; }

    // Resistances
    UFUNCTION(BlueprintPure, BlueprintCallable, meta = (Keywords = "Character Resistances"), Category = "CharacterSheet")
    TArray<FDamageResistance>& GetResistances() { return CharacterSheet.Attributes.Resistances; }

    // Spell buffs/effects
    UFUNCTION(BlueprintCallable, meta = (Keywords = "Character Resistances"), Category = "CharacterSheet")
    void AddSpellEffect(AHealers_Spell* Spell);



    /**
     * Convenience function to find a character sheet associated with a pawn.
     */
    UFUNCTION(BlueprintPure, BlueprintCallable, Category="Healers")
    static AHealers_CharacterSheet* GetCharacterSheet (APawn* SheetOwner);
};


// @! TODO : Need a good way of defining item properties. Suggested: Use GameplayTags. Tags: Weapon, Armor, Accessory, Consumable, etc.
// @! TODO : If using gameplay tags, how do we define what items can exist on a character? (e.g. if we had 'Tail' armor slot available only to enemies with 'Tail' tag, how do we define valid tags for each character? List of tags per CharacterSheet?)
//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Healers|CharacterSheet")
//TArray<AHealers_Inventory*> CharacterInventory;
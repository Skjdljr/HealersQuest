
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Healers_CharacterAttributes.h"
#include "Healers_BattleCoordinator.generated.h"

class AHealers_CharacterSheet;

USTRUCT(BlueprintType, Blueprintable)
struct FBattleData  
{
    GENERATED_BODY();

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Battle Data")
    TArray<AHealers_CharacterSheet*> PartyMembers;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Battle Data")
    TArray<AHealers_CharacterSheet*> EnemyMembers;

    //TODO:
    //Add some representation of waves/level
};

UENUM()
enum EBattleState
{
    BS_PRE_BATTLE = 0,
    BS_BATTLE_IN_PROGRESS,
    BS_POST_BATTLE,
    BS_BATTLE_COMPLETE
};


/////////////////////////////////////////////////////////////////////////////////////////////////
// Delegates

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBattleStateChanged);

/////////////////////////////////////////////////////////////////////////////////////////////////

UCLASS(BlueprintType, NotPlaceable)
class HEALERSQUEST_API AHealers_BattleCoordinator : public AActor
{
    GENERATED_BODY()

    AHealers_BattleCoordinator();

public:

    //Inherited 
    virtual void BeginPlay() override;
    virtual void Tick(float dt) override;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Battle Coordinator")
    FBattleData BattleData;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Battle Coordinator")
    TEnumAsByte<EBattleState> BattleState;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Battle Coordinator")
    TEnumAsByte<EBattleState> PriorBattleState;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Battle Coordinator")
    bool bIsBattleComplete;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Battle Coordinator")
    bool bIsBattleReadyToStart;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Config = "Game", Category = "Battle Coordinator")
    float INITIATIVEMAX = 5.f;

    //Ours
    void SetBattleState(EBattleState newState);

    void TickAllCharacters(float dt);

    UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Battle Coordinator")
    bool IsPartyDefeated();

    UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Battle Coordinator")
    bool IsEnemyDefeated();

    UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Battle Coordinator")
    bool IsBattleComplete();

    UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Battle Coordinator")
    bool IsBattleReadyToStart();

    UFUNCTION(BlueprintCallable, Category = "Battle Coordinator")
    void AddInitiative(float dt, TArray<AHealers_CharacterSheet*> sheet, bool isEnemy);
    
    UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Battle Coordinator")
    AHealers_CharacterSheet* GetRandomEnemyTarget();

    UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Battle Coordinator")
    AHealers_CharacterSheet* GetRandomPartyTarget();
    
    UFUNCTION(BlueprintCallable, Category = "Battle Coordinator")
    void Take_Damage(AHealers_CharacterSheet* defender, AHealers_CharacterSheet* Attacker);

    UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Battle Coordinator")
    float CalculateDamage(FCharacterAttributes& defender, FCharacterAttributes& attacker);

    //todo: duration?
};
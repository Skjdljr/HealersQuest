// Fill out your copyright notice in the Description page of Project Settings.

/////////////////////////////////////////////////////////////////////////////////////////////////

#include "Healers_BattleCoordinator.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

#include "Healers_FunctionLibrary.h"
#include "Healers_CharacterSheet.h"
#include "Healers_PlayerState.h"

/////////////////////////////////////////////////////////////////////////////////////////////////

AHealers_BattleCoordinator::AHealers_BattleCoordinator() :
    BattleState(BS_PRE_BATTLE),
    PriorBattleState(BS_BATTLE_MIN),
    bIsBattleComplete(false),
    bIsBattleReadyToStart(false)
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;
}

void AHealers_BattleCoordinator::BeginPlay()
{
    Super::BeginPlay();
}

void AHealers_BattleCoordinator::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    switch (BattleState)
    {
        case BS_PRE_BATTLE:
        {
            if (BattleState != PriorBattleState)
            {
                UE_LOG(Game, Log, TEXT("Transition to BattleState == BS_PRE_BATTLE."));
                OnBattleStateChanged.Broadcast(BattleState);
                PriorBattleState = BattleState;
            }

            if (IsBattleReadyToStart())
            {
                SetBattleState(BS_BATTLE_IN_PROGRESS);
            }
            break;
        }
        case BS_BATTLE_IN_PROGRESS:
        {
            if (BattleState != PriorBattleState)
            {
                UE_LOG(Game, Log, TEXT("Transition to BattleState == BS_BATTLE_IN_PROGRESS."));
                OnBattleStateChanged.Broadcast(BattleState);
                PriorBattleState = BattleState;
            }

            TickAllCharacters(DeltaTime);

            // Victory or Defeat Conditions
            if (IsEnemyDefeated() || IsPartyDefeated())
            {
                SetBattleState(BS_POST_BATTLE);
            }
            break;
        }
        case BS_POST_BATTLE:
        {
            if (BattleState != PriorBattleState)
            {
                UE_LOG(Game, Log, TEXT("Transition to BattleState == BS_POST_BATTLE."));
                OnBattleStateChanged.Broadcast(BattleState);
                PriorBattleState = BattleState;

                if (IsEnemyDefeated())
                {
                    if (const auto World = GetWorld())
                    {
                        if (auto PC = UGameplayStatics::GetPlayerController(World, 0))
                        {
                            if (auto HealersPlayerState = Cast<AHealers_PlayerState>(PC->PlayerState))
                            {
                                HealersPlayerState->Gold += HealersPlayerState->QuestContract.Reward.Gold;
                                HealersPlayerState->Reputation += HealersPlayerState->QuestContract.Reward.Reputation;
                                UHealers_FunctionLibrary::GetPlayerCharacterSheet(PC)->CharacterSheet.Experience +=
                                    HealersPlayerState->QuestContract.Reward.Experience;
                            }
                        }
                    }

                    OnBattleVictory.Broadcast();
                }
                else if (IsPartyDefeated())
                {
                    OnBattleDefeat.Broadcast();
                }
            }

            //
            if (IsBattleComplete())
            {
                SetBattleState(BS_BATTLE_COMPLETE);
                OnBattleStateChanged.Broadcast(BattleState);
            }
            break;
        }
        default:
        {
            //noop
            break;
        }
    }
}

void AHealers_BattleCoordinator::AddInitiative(float dt, TArray<AHealers_CharacterSheet*> sheet, bool isEnemy)
{
    for (auto member : sheet)
    {
        if (!member->bIsPlayer)
        {
            auto newInitiative = member->GetHealth() > 0
                                     ? member->GetInitiative() + member->GetInitiativePerSecond() * dt
                                     : 0.f;
            member->SetInitiative(newInitiative);

            if (member->GetInitiative() > InitiativeMax)
            {
                auto target = isEnemy ? GetRandomPartyTarget() : GetRandomEnemyTarget();
                if (target != nullptr)
                {
                    member->SetInitiative(0.0f);

                    if (member && target)
                    {
                        UE_LOG(Game, Log, TEXT("Attacker(%s) initiated attack against Defender(%s)"),
                               *member->CharacterSheet.CharacterName, *target->CharacterSheet.CharacterName);
                        Take_Damage(target, member);
                    }
                }
                else
                {
                    UE_LOG(Game, Error, TEXT("You dun goofed, target is null"));
                }
            }
        }
    }
}

void AHealers_BattleCoordinator::TickMana(float dt)
{
    for (auto Member : BattleData.PartyMembers)
    {
        auto NewMana = Member->GetMana() + Member->GetManaRegenerationPerSecond() * dt;
        NewMana = FMath::Clamp(NewMana, 0.f, Member->GetManaMax());
        Member->SetMana(NewMana);
    }

    for (auto Member : BattleData.EnemyMembers)
    {
        auto NewMana = Member->GetMana() + Member->GetManaRegenerationPerSecond() * dt;
        NewMana = FMath::Clamp(NewMana, 0.f, Member->GetManaMax());
        Member->SetMana(NewMana);
    }
}

void AHealers_BattleCoordinator::TickCooldowns(float dt)
{
}

void AHealers_BattleCoordinator::TickAllCharacters(float DeltaTime)
{
    //Need a better name, this also does dmg.... Confusing I know leave me alone
    AddInitiative(DeltaTime, BattleData.EnemyMembers, true);
    AddInitiative(DeltaTime, BattleData.PartyMembers, false);

    TickMana(DeltaTime);
    TickCooldowns(DeltaTime);
}

void AHealers_BattleCoordinator::Take_Damage(AHealers_CharacterSheet* Defender, AHealers_CharacterSheet* attacker)
{
    //TODO? maybe overload actors TakeDamage for now use our own
    //TODO? Maybe overload actors ReceiveAnyDamage?

    if (Defender != nullptr && attacker != nullptr)
    {
        //TODO: actually write the CalculateDamage function
        auto newHealth = CalculateDamage(Defender->GetAttributes(), attacker->GetAttributes());

        UE_LOG(Game, Log, TEXT("Defender(%s) took damage. Health was %f, reduced to %f"),
               *Defender->CharacterSheet.CharacterName, Defender->GetHealth(), newHealth);

        if (newHealth >= 0)
        {
            Defender->SetHealth(newHealth);
        }
        else
        {
            Defender->SetHealth(0);
            UE_LOG(Game, Log, TEXT("Defender(%s) was defeated!"), *Defender->CharacterSheet.CharacterName);

            // Remove them from the list?
        }
    }
    else
    {
        UE_LOG(Game, Error, TEXT("Defender or Attacker null!"));
    }
}

float AHealers_BattleCoordinator::CalculateDamage(FCharacterAttributes& Defender, FCharacterAttributes& Attacker)
{
    //TODO: -Calculate this based of armor/resistances/attackspeed/crit what ever else
    return Defender.Health - FMath::Max(1.f, Attacker.AttackPower - Defender.ArmorValue);
}

AHealers_CharacterSheet* AHealers_BattleCoordinator::GetRandomEnemyTarget()
{
    AHealers_CharacterSheet* Target = nullptr;

    if (!IsPartyDefeated() && !IsEnemyDefeated())
    {
        // Valid Targets match this filter by functor
        TArray<AHealers_CharacterSheet*> ValidTargets = BattleData.EnemyMembers.FilterByPredicate(
            [&](AHealers_CharacterSheet* CharacterSheet)
            {
                return (CharacterSheet
                        ->GetAttributes().Health > 0);
            });

        if (ValidTargets.Num() > 0)
        {
            for (int i = 0; i < ValidTargets.Num(); i++)
            {
                UE_LOG(Game, Log, TEXT("GetRandomEnemyTarget - %s"), *ValidTargets[i]->GetName());
            }

            auto index = FMath::RandRange(0, ValidTargets.Num() - 1);
            Target = ValidTargets[index];
        }
        //need to check the target isn't defeated.... or just remove the defeated ones from the array...
    }

    return Target;
}

AHealers_CharacterSheet* AHealers_BattleCoordinator::GetRandomPartyTarget()
{
    AHealers_CharacterSheet* Target = nullptr;

    if (!IsPartyDefeated() && !IsEnemyDefeated())
    {
        TArray<AHealers_CharacterSheet*> ValidTargets = BattleData.PartyMembers.FilterByPredicate(
            [&](AHealers_CharacterSheet* CharacterSheet)
            {
                return (CharacterSheet
                        ->GetAttributes().Health > 0);
            });

        if (ValidTargets.Num() > 0)
        {
            for (int i = 0; i < ValidTargets.Num(); i++)
            {
                UE_LOG(Game, Log, TEXT("GetRandomPartyTarget - %s"), *ValidTargets[i]->GetName());
            }

            auto index = FMath::RandRange(0, ValidTargets.Num() - 1);
            Target = ValidTargets[index];
        }
        //need to check the target isn't defeated.... or just remove the defeated ones from the array...
    }

    return Target;
}

bool AHealers_BattleCoordinator::IsPartyDefeated()
{
    bool isPartyDefeated = true;

    for (auto member : BattleData.PartyMembers)
    {
        if (member->GetHealth() > 0)
        {
            isPartyDefeated = false;
        }
    }

    return isPartyDefeated;
}

bool AHealers_BattleCoordinator::IsEnemyDefeated()
{
    bool isPartyDefeated = true;

    for (auto member : BattleData.EnemyMembers)
    {
        if (member->GetHealth() > 0)
        {
            isPartyDefeated = false;
        }
    }

    return isPartyDefeated;
}

bool AHealers_BattleCoordinator::IsBattleComplete()
{
    return bIsBattleComplete;
}

bool AHealers_BattleCoordinator::IsBattleReadyToStart()
{
    return bIsBattleReadyToStart;
}

void AHealers_BattleCoordinator::SetBattleState(EBattleState NewState)
{
    if (NewState != BattleState)
    {
        BattleState = NewState;
    }
}

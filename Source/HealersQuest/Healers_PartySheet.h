

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"

#include "Healers_PartySheet.generated.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
// Foward Declarations

class AHealers_CharacterSheet;

/////////////////////////////////////////////////////////////////////////////////////////////////


/**
 * Store Information about our Party
 */
UCLASS(BlueprintType, Blueprintable)
class HEALERSQUEST_API AHealers_PartySheet : public AActor//AInfo
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Healers|PartySheet")
	AHealers_CharacterSheet* PlayerCharacterSheet;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Healers|PartySheet")
	TArray<AHealers_CharacterSheet*> PartyMembers;
	
};

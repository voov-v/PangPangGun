#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PPGMonsterController.generated.h"

enum class EPPGTeamID : uint8;

UCLASS()
class PANGPANGGUN_API APPGMonsterController : public AAIController
{
	GENERATED_BODY()
	
public:
	APPGMonsterController();

	virtual FGenericTeamId GetGenericTeamId() const override;
};

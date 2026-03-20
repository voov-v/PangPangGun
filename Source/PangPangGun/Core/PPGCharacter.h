#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PPGCharacter.generated.h"

UCLASS()
class PANGPANGGUN_API APPGCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APPGCharacter();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

	void ToggleSprint(bool bActive);

private:
	void UpdateMaxWalkSpeed();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float SprintSpeedRate = 2.0f;

private:
	float OriginalWalkSpeed;
	bool bSprinting = false;

};

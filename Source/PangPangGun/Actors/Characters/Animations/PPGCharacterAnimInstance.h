#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Actors/Characters/PPGCharacter.h"
#include "PPGCharacterAnimInstance.generated.h"

class UCharacterMovementComponent;

UCLASS()
class PANGPANGGUN_API UPPGCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float Speed = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bInAir = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsFalling = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	EPPGMovementState MovementState = EPPGMovementState::Idle;

	UPROPERTY()
	TObjectPtr<APPGCharacter> OwningCharacter;

	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> MovementComponent;

};

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"
#include "PPGPlayerController.generated.h"

class APPGCharacter;
struct FInputActionValue;
struct FInputActionInstance;
class UInputMappingContext;
class UInputAction;

UCLASS()
class PANGPANGGUN_API APPGPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

public:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual FGenericTeamId GetGenericTeamId() const override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> SprintAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> AttackAction;

	UPROPERTY()
	TObjectPtr<APPGCharacter> ControlledCharacter;

	bool bInputMove = false;

private:
	void InputMove(const FInputActionInstance& InputActionInstance);
	void OnInputMove(const FInputActionInstance& InputActionInstance);
	void OnInputSprint(const FInputActionInstance& InputActionInstance);
	void OnInputJumpStarted();
	void OnInputAttack();
};

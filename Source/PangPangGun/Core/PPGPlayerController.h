#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PPGPlayerController.generated.h"

class APPGCharacter;
struct FInputActionValue;
struct FInputActionInstance;
class UInputMappingContext;
class UInputAction;

UCLASS()
class PANGPANGGUN_API APPGPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

public:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> SprintAction;

	UPROPERTY()
	TObjectPtr<APPGCharacter> ControlledCharacter;

private:
	void OnInputMoveTriggered(const FInputActionValue& InputActionValue);
	void OnInputSprint(const FInputActionInstance& InputActionInstance);
	void OnInputJumpStarted();
};

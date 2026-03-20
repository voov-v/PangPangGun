#include "Core/PPGPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PPGCharacter.h"

void APPGPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (auto EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
    {
        EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::OnInputMoveTriggered);
        EnhancedInput->BindAction(SprintAction, ETriggerEvent::Started, this, &ThisClass::OnInputSprint);
        EnhancedInput->BindAction(SprintAction, ETriggerEvent::Completed, this, &ThisClass::OnInputSprint);
        EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &ThisClass::OnInputJumpStarted);
    }
}

void APPGPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (auto InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        InputSubsystem->AddMappingContext(InputMappingContext, 0);
    }
}

void APPGPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    ControlledCharacter = Cast<APPGCharacter>(InPawn);
}

void APPGPlayerController::OnUnPossess()
{
    Super::OnUnPossess();

    ControlledCharacter = nullptr;
}

void APPGPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    if (auto InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        InputSubsystem->RemoveMappingContext(InputMappingContext);
    }
}

void APPGPlayerController::OnInputMoveTriggered(const FInputActionValue& InputActionValue)
{
    if (ControlledCharacter == nullptr)
    {
        return;
    }

    const FRotator Rotation = PlayerCameraManager->GetCameraRotation();
    const FRotator YawRotation(0, Rotation.Yaw, 0);

    const FVector ForwardDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    const FVector RightDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    FVector2D InputValue = InputActionValue.Get<FVector2D>();
    ControlledCharacter->AddMovementInput(ForwardDir, InputValue.X);
    ControlledCharacter->AddMovementInput(RightDir, InputValue.Y);
}

void APPGPlayerController::OnInputSprint(const FInputActionInstance& InputActionInstance)
{
    if (ControlledCharacter == nullptr)
    {
        return;
    }

    switch (InputActionInstance.GetTriggerEvent())
    {
    case ETriggerEvent::Started:
        ControlledCharacter->ToggleSprint(true);
        break;
    case ETriggerEvent::Completed:
        ControlledCharacter->ToggleSprint(false);
        break;
    default:
        break;
    }
}

void APPGPlayerController::OnInputJumpStarted()
{
    if (ControlledCharacter == nullptr)
    {
        return;
    }

    ControlledCharacter->Jump();
}

#include "PPGPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PPGCharacter.h"

void APPGPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (auto EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
    {
        EnhancedInput->BindAction(MoveAction, ETriggerEvent::Started, this, &ThisClass::OnInputMove);
        EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::OnInputMove);
        EnhancedInput->BindAction(MoveAction, ETriggerEvent::Completed, this, &ThisClass::OnInputMove);
        EnhancedInput->BindAction(SprintAction, ETriggerEvent::Started, this, &ThisClass::OnInputSprint);
        EnhancedInput->BindAction(SprintAction, ETriggerEvent::Completed, this, &ThisClass::OnInputSprint);
        EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &ThisClass::OnInputJumpStarted);
        EnhancedInput->BindAction(AttackAction, ETriggerEvent::Started, this, &ThisClass::OnInputAttack);
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

FGenericTeamId APPGPlayerController::GetGenericTeamId() const
{
    return ControlledCharacter ? ControlledCharacter->GetGenericTeamId() : FGenericTeamId();
}

void APPGPlayerController::InputMove(const FInputActionInstance& InputActionInstance)
{
    if (ControlledCharacter == nullptr)
    {
        return;
    }

    const FRotator Rotation = PlayerCameraManager->GetCameraRotation();
    const FRotator Rotation2D(0, Rotation.Yaw, 0);

    FVector2D InputValue = InputActionInstance.GetValue().Get<FVector2D>();
    if (InputValue.IsNearlyZero())
    {
        SetControlRotation(ControlledCharacter->GetActorRotation());
        return;
    }

    FVector InputDir = FVector(InputValue, 0.f).GetSafeNormal();
    FVector WorldInputDir = Rotation2D.RotateVector(InputDir);
    ControlledCharacter->AddMovementInput(WorldInputDir);
    SetControlRotation(WorldInputDir.Rotation());
}

void APPGPlayerController::OnInputMove(const FInputActionInstance& InputActionInstance)
{
    switch (InputActionInstance.GetTriggerEvent())
    {
    case ETriggerEvent::Started:
        bInputMove = true;
        InputMove(InputActionInstance);
        break;
    case ETriggerEvent::Triggered:
        InputMove(InputActionInstance);
        break;
    case ETriggerEvent::Completed:
        bInputMove = false;
        return;
    default:
        return;
    }
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

void APPGPlayerController::OnInputAttack()
{
    if (ControlledCharacter == nullptr)
    {
        return;
    }

    auto AttackRotation = ControlledCharacter->GetActorRotation();
    if (bInputMove)
    {
        AttackRotation = GetDesiredRotation();
    }

    ControlledCharacter->Attack(AttackRotation);
}

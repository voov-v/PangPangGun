#include "PPGCharacterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPPGCharacterAnimInstance::NativeInitializeAnimation()
{
    OwningCharacter = Cast<APPGCharacter>(TryGetPawnOwner());
    if (OwningCharacter == nullptr)
    {
        return;
    }

    MovementComponent = OwningCharacter->GetCharacterMovement();
}

void UPPGCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    if (MovementComponent == nullptr)
    {
        return;
    }

    Speed = MovementComponent->Velocity.Size2D();
    bInAir = MovementComponent->IsFalling();
    bIsFalling = MovementComponent->Velocity.Z < 0.f;

    MovementState = OwningCharacter->GetMovementState();
}

#include "Core/PPGCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

APPGCharacter::APPGCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

}

void APPGCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	OriginalWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

void APPGCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	UpdateMaxWalkSpeed();
}

void APPGCharacter::ToggleSprint(bool bActive)
{
	if (bSprinting == bActive)
	{
		return;
	}

	bSprinting = bActive;
	UpdateMaxWalkSpeed();
}

void APPGCharacter::UpdateMaxWalkSpeed()
{
	auto CharMovementComp = GetCharacterMovement();
	CharMovementComp->MaxWalkSpeed = bSprinting ? OriginalWalkSpeed * SprintSpeedRate : OriginalWalkSpeed;
}



#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Character.h"
#include "Team/PPGTeamID.h"
#include "PPGCharacter.generated.h"

class UAnimMontage;
class UMotionWarpingComponent;

UENUM(BlueprintType)
enum class EPPGMovementState : uint8
{
	Idle,
	Walk,
	Run
};

UCLASS()
class PANGPANGGUN_API APPGCharacter : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	APPGCharacter();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual FGenericTeamId GetGenericTeamId() const override { return static_cast<uint8>(TeamID); }

protected:
	virtual bool CanJumpInternal_Implementation() const override;

public:
	FORCEINLINE bool IsSprinting() { return bSprinting; }
	FORCEINLINE bool IsAttacking() const { return bAttacking; }
	FORCEINLINE EPPGMovementState GetMovementState() const { return MovementState; }
	FORCEINLINE EPPGTeamID GetTeamID() const { return TeamID; }
	FORCEINLINE int GetATK() const { return ATK; }
	FORCEINLINE int GetHP() const { return HP; }
	FORCEINLINE bool IsDead() const { return HP <= 0; }

	void ApplyDamage(int Damage);
	void ToggleSprint(bool bActive);
	void Attack(const FRotator& InRotation);

private:
	void HitReact();
	void Die();
	void StopAttack();
	void UpdateMovementState();
	void UpdateMaxWalkSpeed();
	void DebugShowAttackDirection(const FRotator& InRotation);
	void OnAttackMontageBlendingOutStarted(UAnimMontage* Montage, bool bInterrupted);
	void OnHitReactMontageBlendingOutStarted(UAnimMontage* Montage, bool bInterrupted);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<UMotionWarpingComponent> MotionWarpingComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Team")
	EPPGTeamID TeamID = EPPGTeamID::NoTeam;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float SprintSpeedRate = 2.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	TArray<TObjectPtr<UAnimMontage>> HitReactMontages;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	TArray<TObjectPtr<UAnimMontage>> DeathMontages;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	int HP = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	int ATK = 20;

private:
	float OriginalWalkSpeed;
	bool bSprinting = false;
	bool bAttacking = false;
	int HitReactIndex = 0;
	EPPGMovementState MovementState = EPPGMovementState::Idle;

};

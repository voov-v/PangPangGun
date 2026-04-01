#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "PPGAnimNotify_Hitbox.generated.h"

UENUM(BlueprintType)
enum class EPPGHitboxShape : uint8
{
	Sphere,
	Box,
	Capsule
};

UCLASS(DisplayName = "Hitbox")
class PANGPANGGUN_API UPPGAnimNotify_Hitbox : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UPPGAnimNotify_Hitbox();

	virtual FString GetNotifyName_Implementation() const override;
	virtual FLinearColor GetEditorColor() override;

	virtual void BranchingPointNotify(FBranchingPointNotifyPayload& BranchingPointPayload) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hitbox")
	EPPGHitboxShape Shape = EPPGHitboxShape::Sphere;

	//Note: 소켓을 이용하는 방법
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hitbox")
	// FName SoketName = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hitbox")
	FVector Offset = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hitbox", meta = (ClampMin="1.0"))
	float Radius = 50.0f;

private:
	void PerformSphereOverlap(USkeletalMeshComponent* MeshComp) const;
	FVector GetHitboxLocation(USkeletalMeshComponent* MeshComp) const;
	void DrawDebugHitbox(const UWorld* World, const FVector& Center) const;

};

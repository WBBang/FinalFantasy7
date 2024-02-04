// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MBAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FF7_API UMBAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UMBAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	// 공격 애니메이션 실행
	void PlayAttackMontage();

	// 가드 애니메이션 실행
	void PlayGuardMontage();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Pawn, Meta=(AllowPrivateAccess = true))
	float CurrentPawnSpeed;

	UFUNCTION()
	void AnimNotify_MBAttackStartNotify();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta=(AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Guard, Meta = (AllowPrivateAccess = true))
	UAnimMontage* GuardMontage;
};

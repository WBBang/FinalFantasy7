﻿// Fill out your copyright notice in the Description page of Project Settings.

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

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	// 공격 애니메이션 실행
	void PlayAttackMontage();

	// 가드 애니메이션 실행
	void PlayGuardMontage();

	// 지면 충격파 애니메이션 실행
	void PlayShockWaveMontage();

	// 기열파 애니메이션 실행
	void PlayGuardSuccessMontage();

	// 죽는 애니메이션 실행
	void PlayDieMontage();

	UPROPERTY(EditAnywhere)
	class USoundBase* AttackSound; // 사운드

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Pawn, Meta=(AllowPrivateAccess = true))
	float CurrentPawnSpeed;

	UPROPERTY()
	class AMiddleBossCharacter* me;

	UFUNCTION()
	void AnimNotify_MBAttackStartNotify();

	UFUNCTION()
	void AnimNotify_MBAttackEndNotify();

	UFUNCTION()
	void AnimNotify_MBLeftAttackStart();

	UFUNCTION()
	void AnimNotify_MBLeftAttackEnd();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta=(AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Guard, Meta = (AllowPrivateAccess = true))
	UAnimMontage* GuardMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Guard, Meta = (AllowPrivateAccess = true))
	UAnimMontage* ShockWaveMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Guard, Meta = (AllowPrivateAccess = true))
	UAnimMontage* GuardSuccessMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Guard, Meta = ( AllowPrivateAccess = true ))
	UAnimMontage* DieMontage;
};

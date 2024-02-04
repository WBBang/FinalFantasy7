// Fill out your copyright notice in the Description page of Project Settings.


#include "KSH/MBAnimInstance.h"

UMBAnimInstance::UMBAnimInstance()
{
	CurrentPawnSpeed = 0.0f;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack_Montage(TEXT("/ Script / Engine.AnimMontage'/Game/KSH/Animations/Attack/M_AttackMontage.M_AttackMontage'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Guard_Montage(TEXT("/Script/Engine.AnimMontage'/Game/KSH/Animations/Guard/M_Guard_Montage.M_Guard_Montage'"));

	
	if (Attack_Montage.Succeeded())
	{
		AttackMontage = Attack_Montage.Object;
	}

	if (Guard_Montage.Succeeded())
	{
		GuardMontage = Guard_Montage.Object;
	}

}

void UMBAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
	}
}

// 공격 애니메이션
void UMBAnimInstance::PlayAttackMontage()
{
	if (!Montage_IsPlaying(AttackMontage))
	{
		Montage_Play(AttackMontage, 1.0f);
	}
}

// 가드 애니메이션
void UMBAnimInstance::PlayGuardMontage()
{
	if (!Montage_IsPlaying(GuardMontage))
	{
		Montage_Play(GuardMontage, 1.0f);
	}
}


void UMBAnimInstance::AnimNotify_MBAttackStartNotify()
{
	// 공격 판정 추가
}

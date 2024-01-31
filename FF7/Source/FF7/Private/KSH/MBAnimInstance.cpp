// Fill out your copyright notice in the Description page of Project Settings.


#include "KSH/MBAnimInstance.h"

UMBAnimInstance::UMBAnimInstance()
{
	CurrentPawnSpeed = 0.0f;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack_Montage(TEXT("/ Script / Engine.AnimMontage'/Game/KSH/Animations/Attack/M_AttackMontage.M_AttackMontage'"));
	if (Attack_Montage.Succeeded())
	{
		AttackMontage = Attack_Montage.Object;
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

void UMBAnimInstance::PlayAttackMontage()
{
	if (!Montage_IsPlaying(AttackMontage))
	{
		Montage_Play(AttackMontage, 1.0f);
	}
}

void UMBAnimInstance::AnimNotify_MBAttackStartNotify()
{

}

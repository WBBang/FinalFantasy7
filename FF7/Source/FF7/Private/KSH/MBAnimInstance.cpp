// Fill out your copyright notice in the Description page of Project Settings.


#include "KSH/MBAnimInstance.h"
#include "KSH/MiddleBossCharacter.h"

UMBAnimInstance::UMBAnimInstance()
{
	CurrentPawnSpeed = 0.0f;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack_Montage(TEXT("/ Script / Engine.AnimMontage'/Game/KSH/Animations/Attack/M_AttackMontage.M_AttackMontage'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Guard_Montage(TEXT("/Script/Engine.AnimMontage'/Game/KSH/Animations/Guard/M_Guard_Montage.M_Guard_Montage'"));

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ShockWave_Montage(TEXT("/Script/Engine.AnimMontage'/Game/KSH/Animations/ShockWave/M_ShockWaveMontage.M_ShockWaveMontage'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> GuardSuccess_Montage(TEXT("/Script/Engine.AnimMontage'/Game/KSH/Animations/GuardSuccess/M_GuardSuccessMontage.M_GuardSuccessMontage'"));
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Die_Montage(TEXT("/Script/Engine.AnimMontage'/Game/KSH/Animations/Die/M_Die.M_Die'"));

	if (Attack_Montage.Succeeded())
	{
		AttackMontage = Attack_Montage.Object;
	}

	if (Guard_Montage.Succeeded())
	{
		GuardMontage = Guard_Montage.Object;
	}

	if (ShockWave_Montage.Succeeded())
	{
		ShockWaveMontage = ShockWave_Montage.Object;
	}

	if (GuardSuccess_Montage.Succeeded())
	{
		GuardSuccessMontage = GuardSuccess_Montage.Object;
	}

	if ( Die_Montage.Succeeded() )
	{
		DieMontage = Die_Montage.Object;
	}

}

void UMBAnimInstance::NativeInitializeAnimation()
{
	me = Cast<AMiddleBossCharacter>(TryGetPawnOwner());
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

// 지면 충격파 애니메이션
void UMBAnimInstance::PlayShockWaveMontage()
{
	if (!Montage_IsPlaying(ShockWaveMontage))
	{
		Montage_Play(ShockWaveMontage, 1.0f);
	}
}

// 기열파 애니메이션
void UMBAnimInstance::PlayGuardSuccessMontage()
{
	if (!Montage_IsPlaying(GuardSuccessMontage))
	{
		Montage_Play(GuardSuccessMontage, 1.0f);
	}
}

// 사망 애니메이션
void UMBAnimInstance::PlayDieMontage()
{
	if ( !Montage_IsPlaying(DieMontage))
	{
		Montage_Play(DieMontage, 1.0f);
	}
}

void UMBAnimInstance::AnimNotify_MBAttackStartNotify()
{
	// 공격 판정 추가
	me->SetRightHandCompColl(true);
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Blue, TEXT("CollOnRight"));
	//UE_LOG(LogTemp, Log, TEXT("CollOnRight"));
}

void UMBAnimInstance::AnimNotify_MBAttackEndNotify()
{
	// 공격 판정 없애기
	me->SetRightHandCompColl(false);
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Blue, TEXT("CollOffRight"));
	//UE_LOG(LogTemp, Log, TEXT("CollOffRight"));
}

void UMBAnimInstance::AnimNotify_MBLeftAttackStart()
{
	me->SetLeftHandCompColl(true);
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Blue, TEXT("CollOnLeft"));
	//UE_LOG(LogTemp, Log, TEXT("CollOnLeft"));
}

void UMBAnimInstance::AnimNotify_MBLeftAttackEnd()
{
	me->SetLeftHandCompColl(false);
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Blue, TEXT("CollOffLeft"));
	//UE_LOG(LogTemp, Log, TEXT("CollOffLeft"));
}

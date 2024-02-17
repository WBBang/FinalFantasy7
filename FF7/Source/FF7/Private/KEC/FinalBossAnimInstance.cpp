// Fill out your copyright notice in the Description page of Project Settings.


#include "KEC/FinalBossAnimInstance.h"

#include "JWK/Barrett.h"
#include "KEC/FinalBossCharacter.h"
#include "Kismet/GameplayStatics.h"

void UFinalBossAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	me = Cast<AFinalBossCharacter>(TryGetPawnOwner());

	if(me != nullptr)
	{
		finalBossFsm = me->bossFsm;
	}
	else
	{
		return;
	}
	
}

void UFinalBossAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if(finalBossFsm != nullptr)
		return;

	//state = finalBossFsm->state;
}

void UFinalBossAnimInstance::AnimNotify_Attack()
{
	auto barrett = Cast<ABarrett>(GetWorld()->GetFirstPlayerController()->GetPawn());
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Test!"));
	barrett->BarrettDamaged(20);
}

void UFinalBossAnimInstance::AnimNotify_Launch()
{
		
	if( me != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Test!"));
		me->LauchMissile();
	}
} 

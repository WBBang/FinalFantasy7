// Fill out your copyright notice in the Description page of Project Settings.


#include "KEC/FinalBossAnimInstance.h"

#include "JWK/Barrett.h"
#include "KEC/FinalBossCharacter.h"

void UFinalBossAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	auto owner = TryGetPawnOwner();
	if(owner != nullptr)
		return;

	//AFinalBossCharacter* me = Cast<AFinalBossCharacter>(owner);
	//finalBossFsm = me->bossFsm;
	
		
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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Test!"));
	barrett->BarrettDamaged(20);
}

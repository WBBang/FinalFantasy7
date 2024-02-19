// Fill out your copyright notice in the Description page of Project Settings.


#include "KEC/FinalBossFSM.h"

#include "Components/ArrowComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KEC/FinalBossCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UFinalBossFSM::UFinalBossFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFinalBossFSM::BeginPlay()
{
	Super::BeginPlay();

	me = Cast<AFinalBossCharacter>(GetOwner());
	target = GetWorld()->GetFirstPlayerController()->GetPawn();
	// 보스 총구 Transfrom 가져오기
	leftGun = me->leftArrowComp->GetComponentTransform();
	rightGun = me->rightArrowComp->GetComponentTransform();
}


// Called every frame
void UFinalBossFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	switch (state)
	{
		case EFinalBossState::IDLE:				TickIdle();				break;
		case EFinalBossState::MOVE:				TickMove();				break;
		case EFinalBossState::NORMALATTACK:		TickNormalAttack();		break;
		case EFinalBossState::LAUNCHBOMB:		TickLaunchBomb();		break;
		case EFinalBossState::FIREMISSILE:		TickFireMissile();		break;
		case EFinalBossState::RUSH:				TickRush();				break;
		case EFinalBossState::JUMPATTACK:		TickJumpAttack();		break;
		case EFinalBossState::GROGGY:			TickGroggy();			break;
		case EFinalBossState::DEAD:				TickDead();				break;
	}
}

void UFinalBossFSM::TickIdle()
{
	if(me->playerLength < detectRange)
		SetState(EFinalBossState::MOVE);
	
	if(me->isDead == true)
		SetState(EFinalBossState::DEAD);

	if(me->isSecondPhase == true)
		SetState(EFinalBossState::LAUNCHBOMB);
}

void UFinalBossFSM::TickMove()
{
	FVector dir = target->GetActorLocation() - me->GetActorLocation();
	me->AddMovementInput(dir.GetSafeNormal());
	float length = target->GetDistanceTo(me);
	
	if(length < attackLength)
	 	SetState(EFinalBossState::NORMALATTACK);

	else if (length > detectRange && normalAttackCount > 3)
	{
	 	SetState(EFinalBossState::JUMPATTACK);
		normalAttackCount = 0;
	}
	
	else if (length > detectRange)
	{
		rushStartVector = me->GetActorLocation();
	 	SetState(EFinalBossState::RUSH);
	}

	if(me->isDead == true)
		SetState(EFinalBossState::DEAD);
}

void UFinalBossFSM::TickNormalAttack()
{

	if(me->isDead == true)
		SetState(EFinalBossState::DEAD);

	else if(me->isSecondPhase == true)
		SetState(EFinalBossState::LAUNCHBOMB);

	
	float length = target->GetDistanceTo(me);
	currentTime += GetWorld()->GetDeltaSeconds();
	normalAttackCount++;

	if(length > attackLength)
		{
			SetState(EFinalBossState::MOVE);
		}

}

void UFinalBossFSM::TickFireMissile()
{
	if(me->isDead == true)
		SetState(EFinalBossState::DEAD);
	
	SetState(EFinalBossState :: IDLE);
}

void UFinalBossFSM::TickLaunchBomb()
{
	//SetState(EFinalBossState :: MOVE);

	if(me->isDead == true)
		SetState(EFinalBossState::DEAD);
}


void UFinalBossFSM::TickRush()
{
	if(me->isDead == true)
		SetState(EFinalBossState::DEAD);
	
	FVector dir = target->GetActorLocation() - me->GetActorLocation();
	dir.Normalize();
	float dist = (me->GetActorLocation() - rushStartVector).Size();
	if(dist < 3000)
	{
		me->SetActorLocation(me->GetActorLocation() + dir * rushSpeed * GetWorld()->DeltaTimeSeconds);
	}
	FTimerHandle MyTimer;
	float Time = 1.25f;
	GetWorld()->GetTimerManager().SetTimer(MyTimer, FTimerDelegate::CreateLambda([&]()
	   {
		
		SetState(EFinalBossState :: GROGGY);

		GetWorld()->GetTimerManager().ClearTimer(MyTimer);
	   }), Time, false);
}

void UFinalBossFSM::TickJumpAttack()
{
	if(me->isDead == true)
		SetState(EFinalBossState::DEAD);
	
	float dist = (me->GetActorLocation() - rushStartVector).Size();
	if(dist < 2000)
	{
		me->GetCharacterMovement()->SetMovementMode(MOVE_None);
		me->SetActorLocation(me->GetActorLocation() + me->GetActorForwardVector() * 1000 * GetWorld()->DeltaTimeSeconds);
	}
	FTimerHandle MyTimer;
	float Time = 1.25f;
	GetWorld()->GetTimerManager().SetTimer(MyTimer, FTimerDelegate::CreateLambda([&]()
	   {
		
		SetState(EFinalBossState :: MOVE);

		GetWorld()->GetTimerManager().ClearTimer(MyTimer);
	   }), Time, false);
}

void UFinalBossFSM::TickGroggy()
{
	if(me->isDead == true)
		SetState(EFinalBossState::DEAD);
	
	FTimerHandle MyTimer;
	float Time = 5.0f;
	GetWorld()->GetTimerManager().SetTimer(MyTimer, FTimerDelegate::CreateLambda([&]()
	   {
		  UE_LOG(LogTemp, Log, TEXT("bye"));
		  // 실행할 내용

	SetState(EFinalBossState :: MOVE);
		  // TimerHandle 초기화
		  GetWorld()->GetTimerManager().ClearTimer(MyTimer);
	   }), Time, false);
}

void UFinalBossFSM::TickDead()
{
	me->GetCharacterMovement()->SetMovementMode(MOVE_None);
}

void UFinalBossFSM::SetState(EFinalBossState next)
{
	state = next;
	currentTime = 0;
}


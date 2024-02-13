// Fill out your copyright notice in the Description page of Project Settings.


#include "KEC/FinalBossFSM.h"

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

	// ...
	me = Cast<AFinalBossCharacter>(GetOwner());
	
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
		case EFinalBossState::FireMissile:		TickFireMissile();		break;
		case EFinalBossState::RUSH:				TickRush();				break;
		case EFinalBossState::JUMPATTACK:		TickJumpAttack();		break;
		case EFinalBossState::GROGGY:			TickGroggy();			break;
		case EFinalBossState::DEAD:				TickDead();				break;
	}
}

void UFinalBossFSM::TickIdle()
{
	target = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if(me->playerLength < detectRange)
		SetState(EFinalBossState::MOVE);
	
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

	
}

void UFinalBossFSM::TickNormalAttack()
{
	float length = target->GetDistanceTo(me);
	currentTime += GetWorld()->GetDeltaSeconds();
	normalAttackCount++;
		if(length > attackLength)
		{
			SetState(EFinalBossState::MOVE);
		}
		
		else
		{
			UE_LOG( LogTemp , Warning , TEXT( "Enemy->Player Attack!!!" ) );
		}
}
		



void UFinalBossFSM::TickFireMissile()
{
	SetState(EFinalBossState :: IDLE);
}

void UFinalBossFSM::TickLaunchBomb()
{
}


void UFinalBossFSM::TickRush()
{
	float dist = (me->GetActorLocation() - rushStartVector).Size();
	if(dist < 3000)
	{
		me->SetActorLocation(me->GetActorLocation() + me->GetActorForwardVector() * rushSpeed * GetWorld()->DeltaTimeSeconds);
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
	float dist = (me->GetActorLocation() - rushStartVector).Size();
	if(dist < 3000)
	{
		me->SetActorLocation(me->GetActorLocation() + me->GetActorForwardVector() * rushSpeed * GetWorld()->DeltaTimeSeconds);
	}
	FTimerHandle MyTimer;
	float Time = 1.25f;
	GetWorld()->GetTimerManager().SetTimer(MyTimer, FTimerDelegate::CreateLambda([&]()
	   {
		
		SetState(EFinalBossState :: IDLE);

		GetWorld()->GetTimerManager().ClearTimer(MyTimer);
	   }), Time, false);
}

void UFinalBossFSM::TickGroggy()
{
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
	
}

void UFinalBossFSM::SetState(EFinalBossState next)
{
	state = next;
	currentTime = 0;
}


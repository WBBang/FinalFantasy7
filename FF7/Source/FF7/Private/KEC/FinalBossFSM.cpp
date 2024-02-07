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
		case EFinalBossState::GROGGY:			TickGroggy();			break;
		case EFinalBossState::DEAD:				TickDead();				break;
	}
}

void UFinalBossFSM::TickIdle()
{
	target = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if(me->playerLength < 1000)
		SetState(EFinalBossState::MOVE);
	
}

void UFinalBossFSM::TickMove()
{
	FVector dir = target->GetActorLocation() - me->GetActorLocation();
	me->AddMovementInput(dir.GetSafeNormal());
	float length = target->GetDistanceTo(me);
	UE_LOG( LogTemp , Warning , TEXT( "Enemy->Player Attack!!!" ) );
	if(length < attackLength)
	 	SetState(EFinalBossState::NORMALATTACK);
}

void UFinalBossFSM::TickNormalAttack()
{
	float length = target->GetDistanceTo(me);
	currentTime += GetWorld()->GetDeltaSeconds();
	if(currentTime > normalAttackCooldown)
	{
		currentTime = 0;
		if(length > attackLength)
		{
			SetState(EFinalBossState::MOVE);
		}
		
		else
		{
			UE_LOG( LogTemp , Warning , TEXT( "Enemy->Player Attack!!!" ) );
		}
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
}

void UFinalBossFSM::TickGroggy()
{
}

void UFinalBossFSM::TickDead()
{
}

void UFinalBossFSM::SetState(EFinalBossState next)
{
	state = next;
	currentTime = 0;
}


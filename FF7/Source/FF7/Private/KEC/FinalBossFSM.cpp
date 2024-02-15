// Fill out your copyright notice in the Description page of Project Settings.


#include "KEC/FinalBossFSM.h"

#include "Components/ArrowComponent.h"
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
		case EFinalBossState::GATLINGATTACK:	TickGatlingAttack();		break;
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
	SetState(EFinalBossState::GATLINGATTACK);
}

void UFinalBossFSM::TickGatlingAttack()
{
	//보스 양쪽 애로우에서 LineTrace를 발사 -> 플레이어 방향
	FHitResult outHitLeft;
	FHitResult outHitRight;
	FCollisionQueryParams params;
	params.AddIgnoredActor(me);
	//왼쪽 발사
	FVector leftEnd = leftGun.GetLocation().ForwardVector * 1000000;
	bool bReturnValueLeft = GetWorld()->LineTraceSingleByChannel(outHitLeft,leftGun.GetLocation(), leftEnd, ECC_Visibility, params );

	if(bReturnValueLeft)
	{
		//발사하면서 왼쪽 애로우에 VFX 스폰
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),me->fireVFX,leftGun.GetLocation());
		DrawDebugLine(GetWorld(),outHitLeft.TraceStart, outHitLeft.ImpactPoint, FColor::Red, false, 5);
		//적중한 컴포넌트
		UPrimitiveComponent* hitComp = outHitLeft.GetComponent();
		if(hitComp)
		{
			//적중한 위치에 vfx생성
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),me->fireVFX,outHitLeft.ImpactPoint);
		}
	}
	//오른쪽 발사
	FVector rightEnd = rightGun.GetLocation().ForwardVector * 1000000;
	bool bReturnValueRight = GetWorld()->LineTraceSingleByChannel(outHitRight,rightGun.GetLocation(), rightEnd, ECC_Visibility, params );
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),me->fireVFX,rightGun.GetLocation());

	if(bReturnValueRight)
	{
		//발사하면서 오른쪽 애로우에 VFX 스폰
		DrawDebugLine(GetWorld(),outHitRight.TraceStart, outHitRight.ImpactPoint, FColor::Red, false, 5);
		UPrimitiveComponent* hitComp = outHitRight.GetComponent();
		if(hitComp)
		{
			//적중한 위치에 vfx생성
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),me->fireVFX,outHitRight.ImpactPoint);
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


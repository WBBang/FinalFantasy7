// Fill out your copyright notice in the Description page of Project Settings.

#include "KSH/MiddleBossCharacter.h"
#include "KSH/MBAIController.h"
#include "KSH/MBAnimInstance.h"
#include "KSH/ShockWaveAOE.h"
#include "GuardSuccessAOE.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include <BehaviorTree/BehaviorTreeComponent.h>


// Sets default values
AMiddleBossCharacter::AMiddleBossCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AMBAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	IsAttacking = false;
	IsGuarding = false;
	GuardingDamage = 0.0f;
}

// Called when the game starts or when spawned
void AMiddleBossCharacter::BeginPlay()
{
	Super::BeginPlay();
	MiddleBossHP = MiddleBossMaxHP;
	movementComp = GetCharacterMovement();
}

// Called every frame
void AMiddleBossCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// 델리게이트가 발생할 때까지 몽타주 재생 명령 내리지 못하게
void AMiddleBossCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	auto AnimInstance = Cast<UMBAnimInstance>(GetMesh()->GetAnimInstance());
	if (nullptr == AnimInstance) return;

	AnimInstance->OnMontageEnded.AddDynamic(this, &AMiddleBossCharacter::OnMontageEnded);
}

// Called to bind functionality to input
void AMiddleBossCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// 기본 스킬로 맞은 경우
void AMiddleBossCharacter::MiddleBossDamagedByBasicBullet(float damage)
{
	// 보스한테 데미지 처리
	MiddleBossDamaged(damage);
}

// 우와아왕빵으로 맞은 경우
void AMiddleBossCharacter::MiddleBossDamagedBySkillBullet(float damage)
{
	// 가드 상태가 아니라면
	if (false == IsGuarding)
	{
		// 경직 상태
		IsHitStuning = true;

		// 경직 애니메이션 호출


		// 경직 애니메이션 끝날 때 IsHitStuning = false 처리 하기
	}

	// 보스한테 데미지 처리
	MiddleBossDamaged(damage);
}

// 플레이어에게 공격 당한 경우 (어떤 공격이든 항상 호출)
void AMiddleBossCharacter::MiddleBossDamaged(float damage)
{
	// 가드 중이라면
	if (true == IsGuarding)
	{
		// 피 줄어드는 대신 가드에 데미지 누적
		GuardingDamage += damage;

		// 가드 데미지가 카운터 가능 데미지(CounterDamage)까지 도달했고
		// 기열파 실행중이 아니라면
		if (GuardingDamage >= 2 && !IsGuardSuccess)
		{
			UE_LOG(LogTemp, Log, TEXT("IsGuardSuccessing"));

			// 가드 성공
			IsGuardSuccess = true;
		}
	}

	// 가드 중이 아니라면
	else
	{
		// 데미지 받고
		MiddleBossHP -= damage;

		// 0이하라면
		if (MiddleBossHP <= 0)
		{
			MiddleBossHP = 0;

			// 중간보스 클리어 처리
			
		}

		// 30% 확률로 
		int randomNum = FMath::RandRange(0, 9);
		if (randomNum < 3) // 0, 1, 2
		{
			Guard();
		}
	}
}

void AMiddleBossCharacter::SetIsGuarding(bool isGuarding)
{
	IsGuarding = isGuarding;
}

// 가드
void AMiddleBossCharacter::Guard()
{
	if (IsGuarding) return;
	GuardingDamage = 0.0f;
	IsGuarding = true;
	IsGuardSuccess = false;

	auto AnimInstance = Cast<UMBAnimInstance>(GetMesh()->GetAnimInstance());
	if (nullptr == AnimInstance) return;

	AnimInstance->PlayGuardMontage();
}

// 기본 공격
void AMiddleBossCharacter::Attack()
{
	if (IsAttacking) return;

	auto AnimInstance = Cast<UMBAnimInstance>(GetMesh()->GetAnimInstance());
	if (nullptr == AnimInstance) return;

	AnimInstance->PlayAttackMontage();
	IsAttacking = true;
}

// 애니메이션 끝
void AMiddleBossCharacter::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	// 평타 몽타주였다면
	if (Montage->GetFName() == "M_AttackMontage")
	{
		UE_LOG(LogTemp, Log, TEXT("Attack Montage End"));
		IsAttacking = false;

		// 공격 판정 없애기

	}

	// 가드 몽타주였다면
	else if (Montage->GetFName() == "M_Guard_Montage")
	{
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, TEXT("Guard End"));
		UE_LOG(LogTemp, Log, TEXT("Guard Montage End"));

		// 가드 관련 변수 초기화
		GuardingDamage = 0.0f;
		//IsGuarding = false;
	}

	// 지면 충격파 몽타주였다면
	else if (Montage->GetFName() == "M_ShockWaveMontage")
	{
		IsShockWaving = false;
		OnShockWaveFinished.ExecuteIfBound();
		return;
	}

	// 기열파 몽타주였다면
	else if (Montage->GetFName() == "M_GuardSuccessMontage")
	{
		// 애니메이션 관련 변수 초기화
		IsGuardSuccessing = false;

		UE_LOG(LogTemp, Log, TEXT("GuardSuccess End"));

		// 가드 관련 변수 초기화
		GuardingDamage = 0.0f;
		IsGuarding = false;
		IsGuardSuccess = false;
	}

	// BT에 끝난거 알려주기
	// 나중에 몽타주별로 나눠야 함 (우선은 귀찮으니 하나로..ㅎ)
	OnAttackFinished.ExecuteIfBound();
}

// 가드 성공 - 기열파
void AMiddleBossCharacter::GuardSuccess()
{
	if (IsGuardSuccessing) return;

	auto AnimInstance = Cast<UMBAnimInstance>(GetMesh()->GetAnimInstance());
	if (nullptr == AnimInstance) return;

	AnimInstance->PlayGuardSuccessMontage();

	player = GetWorld()->GetFirstPlayerController()->GetPawn();
	FVector loc = FVector(player->GetActorLocation().X, player->GetActorLocation().Y, player->GetActorLocation().Z - 90.0f);
	GetWorld()->SpawnActor<AGuardSuccessAOE>(aoeActor, loc, FRotator(0, 0, 0));

	IsGuardSuccessing = true;
}

// 지면 충격파
void AMiddleBossCharacter::ShockWave()
{
	if (IsShockWaving) return;

	auto AnimInstance = Cast<UMBAnimInstance>(GetMesh()->GetAnimInstance());
	if (nullptr == AnimInstance) return;

	AnimInstance->PlayShockWaveMontage();

	FVector loc = FVector(GetActorLocation().X, GetActorLocation().Y, 30.0f);
	GetWorld()->SpawnActor<AShockWaveAOE>(shockWaveActor, loc, FRotator(0, 0, 0));

	IsShockWaving = true;
}

// 랜덤 순찰 범위
float AMiddleBossCharacter::GetAIPatrolRadius()
{
	return 800.0f;
}

// 플레이어 인지 범위
float AMiddleBossCharacter::GetAIDetectRange()
{
	return 2000.0f;
}

// 플레이어 공격할 수 있는 범위
float AMiddleBossCharacter::GetAIAttackRange()
{
	canAttackRange = 1000.0f;
	return canAttackRange;
}

// 플레이어에게 스킬쓸 수 있는 범위
float AMiddleBossCharacter::GetAISkillRange()
{
	canSkillRange = 1500.0f;
	return canSkillRange;
}

float AMiddleBossCharacter::GetAITurnSpeed()
{
	return 0.0f;
}

bool AMiddleBossCharacter::GetAIGuardingSuccess()
{
	return IsGuardSuccess;
}

bool AMiddleBossCharacter::GetAIGuarding()
{
	return IsGuarding;
}

void AMiddleBossCharacter::SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished)
{
	OnAttackFinished = InOnAttackFinished;
}

void AMiddleBossCharacter::SetAIShockWaveDelegate(const FAICharacterShockWaveFinished& InOnShockWaveFinished)
{
	OnShockWaveFinished = InOnShockWaveFinished;
}

void AMiddleBossCharacter::AttackByAI()
{
	// 공격
	Attack();
}

void AMiddleBossCharacter::ShockWaveByAI()
{
	ShockWave();
}

void AMiddleBossCharacter::GuardSuccessByAI()
{
	GuardSuccess();
}

// 스피드 변환 함수
void AMiddleBossCharacter::SpeedChangeByAI(float Speed)
{
	movementComp->MaxWalkSpeed = Speed;
}


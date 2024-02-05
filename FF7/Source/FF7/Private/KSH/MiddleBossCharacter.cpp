// Fill out your copyright notice in the Description page of Project Settings.

#include "KSH/MiddleBossCharacter.h"
#include "KSH/MBAIController.h"
#include "KSH/MBAnimInstance.h"
#include "KSH/ShockWaveAOE.h"
#include "GuardSuccessAOE.h"


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

// 플레이어에게 공격 당한 경우
void AMiddleBossCharacter::MiddleBossDamaged(float damage)
{
	// 가드 중이라면
	if (true == IsGuarding)
	{
		// 피 줄어드는 대신 가드에 데미지 누적
		GuardingDamage += damage;
	}
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

// 기본 공격 애니메이션 끝
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
		IsGuarding = false;

		// 가드 데미지 초기화

	}

	// BT에 끝난거 알려주기
	OnAttackFinished.ExecuteIfBound();
}

// 가드 성공 - 기열파
void AMiddleBossCharacter::GuardSuccess()
{
	player = GetWorld()->GetFirstPlayerController()->GetPawn();
	FVector loc = FVector(player->GetActorLocation().X, player->GetActorLocation().Y, player->GetActorLocation().Z - 90.0f);
	GetWorld()->SpawnActor<AGuardSuccessAOE>(aoeActor, loc, FRotator(0, 0, 0));
}

void AMiddleBossCharacter::ShockWave()
{
	FVector loc = FVector(GetActorLocation().X, GetActorLocation().Y, 30.0f);
	GetWorld()->SpawnActor<AShockWaveAOE>(shockWaveActor, loc, FRotator(0, 0, 0));
}

// 가드
void AMiddleBossCharacter::Guard()
{
	if (IsGuarding) return;

	auto AnimInstance = Cast<UMBAnimInstance>(GetMesh()->GetAnimInstance());
	if (nullptr == AnimInstance) return;

	AnimInstance->PlayGuardMontage();

	// 누적 데미지 초기화 후 증가 시키기 (증가 : 에서)
	GuardingDamage = 0.0f;
	IsGuarding = true;
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

void AMiddleBossCharacter::SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished)
{
	OnAttackFinished = InOnAttackFinished;
}

void AMiddleBossCharacter::AttackByAI()
{
	// 공격
	//Attack();

	Guard();
}



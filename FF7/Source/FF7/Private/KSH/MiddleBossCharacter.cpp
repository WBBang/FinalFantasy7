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

// ��������Ʈ�� �߻��� ������ ��Ÿ�� ��� ��� ������ ���ϰ�
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

// �⺻ ��ų�� ���� ���
void AMiddleBossCharacter::MiddleBossDamagedByBasicBullet(float damage)
{
	// �������� ������ ó��
	MiddleBossDamaged(damage);
}

// ��;ƿջ����� ���� ���
void AMiddleBossCharacter::MiddleBossDamagedBySkillBullet(float damage)
{
	// ���� ���°� �ƴ϶��
	if (false == IsGuarding)
	{
		// ���� ����
		IsHitStuning = true;

		// ���� �ִϸ��̼� ȣ��


		// ���� �ִϸ��̼� ���� �� IsHitStuning = false ó�� �ϱ�
	}

	// �������� ������ ó��
	MiddleBossDamaged(damage);
}

// �÷��̾�� ���� ���� ��� (� �����̵� �׻� ȣ��)
void AMiddleBossCharacter::MiddleBossDamaged(float damage)
{
	// ���� ���̶��
	if (true == IsGuarding)
	{
		// �� �پ��� ��� ���忡 ������ ����
		GuardingDamage += damage;

		// ���� �������� ī���� ���� ������(CounterDamage)���� �����߰�
		// �⿭�� �������� �ƴ϶��
		if (GuardingDamage >= 2 && !IsGuardSuccess)
		{
			UE_LOG(LogTemp, Log, TEXT("IsGuardSuccessing"));

			// ���� ����
			IsGuardSuccess = true;
		}
	}

	// ���� ���� �ƴ϶��
	else
	{
		// ������ �ް�
		MiddleBossHP -= damage;

		// 0���϶��
		if (MiddleBossHP <= 0)
		{
			MiddleBossHP = 0;

			// �߰����� Ŭ���� ó��
			
		}

		// 30% Ȯ���� 
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

// ����
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

// �⺻ ����
void AMiddleBossCharacter::Attack()
{
	if (IsAttacking) return;

	auto AnimInstance = Cast<UMBAnimInstance>(GetMesh()->GetAnimInstance());
	if (nullptr == AnimInstance) return;

	AnimInstance->PlayAttackMontage();
	IsAttacking = true;
}

// �ִϸ��̼� ��
void AMiddleBossCharacter::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	// ��Ÿ ��Ÿ�ֿ��ٸ�
	if (Montage->GetFName() == "M_AttackMontage")
	{
		UE_LOG(LogTemp, Log, TEXT("Attack Montage End"));
		IsAttacking = false;

		// ���� ���� ���ֱ�

	}

	// ���� ��Ÿ�ֿ��ٸ�
	else if (Montage->GetFName() == "M_Guard_Montage")
	{
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, TEXT("Guard End"));
		UE_LOG(LogTemp, Log, TEXT("Guard Montage End"));

		// ���� ���� ���� �ʱ�ȭ
		GuardingDamage = 0.0f;
		//IsGuarding = false;
	}

	// ���� ����� ��Ÿ�ֿ��ٸ�
	else if (Montage->GetFName() == "M_ShockWaveMontage")
	{
		IsShockWaving = false;
		OnShockWaveFinished.ExecuteIfBound();
		return;
	}

	// �⿭�� ��Ÿ�ֿ��ٸ�
	else if (Montage->GetFName() == "M_GuardSuccessMontage")
	{
		// �ִϸ��̼� ���� ���� �ʱ�ȭ
		IsGuardSuccessing = false;

		UE_LOG(LogTemp, Log, TEXT("GuardSuccess End"));

		// ���� ���� ���� �ʱ�ȭ
		GuardingDamage = 0.0f;
		IsGuarding = false;
		IsGuardSuccess = false;
	}

	// BT�� ������ �˷��ֱ�
	// ���߿� ��Ÿ�ֺ��� ������ �� (�켱�� �������� �ϳ���..��)
	OnAttackFinished.ExecuteIfBound();
}

// ���� ���� - �⿭��
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

// ���� �����
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

// ���� ���� ����
float AMiddleBossCharacter::GetAIPatrolRadius()
{
	return 800.0f;
}

// �÷��̾� ���� ����
float AMiddleBossCharacter::GetAIDetectRange()
{
	return 2000.0f;
}

// �÷��̾� ������ �� �ִ� ����
float AMiddleBossCharacter::GetAIAttackRange()
{
	canAttackRange = 1000.0f;
	return canAttackRange;
}

// �÷��̾�� ��ų�� �� �ִ� ����
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
	// ����
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

// ���ǵ� ��ȯ �Լ�
void AMiddleBossCharacter::SpeedChangeByAI(float Speed)
{
	movementComp->MaxWalkSpeed = Speed;
}


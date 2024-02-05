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

// �÷��̾�� ���� ���� ���
void AMiddleBossCharacter::MiddleBossDamaged(float damage)
{
	// ���� ���̶��
	if (true == IsGuarding)
	{
		// �� �پ��� ��� ���忡 ������ ����
		GuardingDamage += damage;
	}
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

// �⺻ ���� �ִϸ��̼� ��
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
		IsGuarding = false;

		// ���� ������ �ʱ�ȭ

	}

	// BT�� ������ �˷��ֱ�
	OnAttackFinished.ExecuteIfBound();
}

// ���� ���� - �⿭��
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

// ����
void AMiddleBossCharacter::Guard()
{
	if (IsGuarding) return;

	auto AnimInstance = Cast<UMBAnimInstance>(GetMesh()->GetAnimInstance());
	if (nullptr == AnimInstance) return;

	AnimInstance->PlayGuardMontage();

	// ���� ������ �ʱ�ȭ �� ���� ��Ű�� (���� : ����)
	GuardingDamage = 0.0f;
	IsGuarding = true;
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

void AMiddleBossCharacter::SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished)
{
	OnAttackFinished = InOnAttackFinished;
}

void AMiddleBossCharacter::AttackByAI()
{
	// ����
	//Attack();

	Guard();
}



// Fill out your copyright notice in the Description page of Project Settings.

#include "KSH/MiddleBossCharacter.h"
#include "KSH/MBAIController.h"
#include "KSH/MBAnimInstance.h"


// Sets default values
AMiddleBossCharacter::AMiddleBossCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AMBAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	IsAttacking = false;
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

	AnimInstance->OnMontageEnded.AddDynamic(this, &AMiddleBossCharacter::OnAttackMontageEnded);
}

// Called to bind functionality to input
void AMiddleBossCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

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

void AMiddleBossCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	//UE_LOG(LogTemp, Log, TEXT("Attack Montage End"));
	IsAttacking = false;
	OnAttackFinished.ExecuteIfBound();
}

// 애니메이션 끝났을 때 호출
void AMiddleBossCharacter::NotifyComboActionEnd()
{
	OnAttackFinished.ExecuteIfBound();
}

float AMiddleBossCharacter::GetAIPatrolRadius()
{
	return 800.0f;
}

float AMiddleBossCharacter::GetAIDetectRange()
{
	return 400.0f;
}

float AMiddleBossCharacter::GetAIAttackRange()
{
	return 100.0f;
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
	Attack();
}


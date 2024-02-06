// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KSH//MBCharacterAIInterface.h"
#include "MiddleBossCharacter.generated.h"

UCLASS()
class FF7_API AMiddleBossCharacter : public ACharacter, public IMBCharacterAIInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMiddleBossCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public: 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* skeletalMesh;

	// 기열파 장판
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackSkill)
	TSubclassOf<class AGuardSuccessAOE> aoeActor;

	// 지면 충격파 불덩이
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackSkill)
	TSubclassOf<class AShockWaveAOE> shockWaveActor;

	// 공격 범위
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackSkill)
	float canAttackRange;

	// 스킬 범위
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackSkill)
	float canSkillRange;

	// 플레이어에게 기본 공격으로 맞은 경우
	UFUNCTION()
	void MiddleBossDamagedByBasicBullet(float damage);
	
	// 플레이어에게 스킬 공격으로 맞은 경우
	UFUNCTION()
	void MiddleBossDamagedBySkillBullet(float damage);
	
	// 공격 당함
	UFUNCTION(BlueprintCallable)
	void MiddleBossDamaged(float damage);

	
private:

	// 플레이어
	UPROPERTY()
	class AActor* player;

	void Attack();

	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = AttackSkill, Meta=(AllowPrivateAccess = true))
	bool IsAttacking;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = AttackSkill, Meta = (AllowPrivateAccess = true))
	bool IsGuarding;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = AttackSkill, Meta = (AllowPrivateAccess = true))
	bool IsGuardSuccessing;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = AttackSkill, Meta = (AllowPrivateAccess = true))
	bool IsShockWaving;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = AttackSkill, Meta = (AllowPrivateAccess = true))
	float GuardingDamage;

	// 경직중인지 판단
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attacked, Meta = (AllowPrivateAccess = true))
	bool IsHitStuning;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attacked, Meta = (AllowPrivateAccess = true))
	float CounterDamage = 30.0f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Moving, Meta = (AllowPrivateAccess = true))
	class UCharacterMovementComponent* movementComp;


	// 기열파
	void GuardSuccess();

	// 지면 충격파
	void ShockWave();

	// 가드
	void Guard();


	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Moving, Meta = (AllowPrivateAccess = true))
	float MiddleBossHP;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Moving, Meta = (AllowPrivateAccess = true))
	float MiddleBossMaxHP = 500.0f;

// AI Section
protected:
	virtual float GetAIPatrolRadius() override;
	virtual float GetAIDetectRange() override;
	virtual float GetAIAttackRange() override;
	virtual float GetAISkillRange() override;
	virtual float GetAITurnSpeed() override;

	virtual void SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished) override;
	virtual void SetAIShockWaveDelegate(const FAICharacterShockWaveFinished& InOnShockWaveFinished) override;
	virtual void AttackByAI() override;
	virtual void ShockWaveByAI() override;

	virtual void SpeedChangeByAI(float Speed) override;

	// 전달받은 델리게이트를 보관하는 함수
	FAICharacterAttackFinished OnAttackFinished;
	FAICharacterShockWaveFinished OnShockWaveFinished;
};

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

	// �⿭�� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackSkill)
	TSubclassOf<class AGuardSuccessAOE> aoeActor;

	// ���� ����� �ҵ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackSkill)
	TSubclassOf<class AShockWaveAOE> shockWaveActor;

	// ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackSkill)
	float canAttackRange;

	// ��ų ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackSkill)
	float canSkillRange;

	// �÷��̾�� �⺻ �������� ���� ���
	UFUNCTION()
	void MiddleBossDamagedByBasicBullet(float damage);
	
	// �÷��̾�� ��ų �������� ���� ���
	UFUNCTION()
	void MiddleBossDamagedBySkillBullet(float damage);
	
	// ���� ����
	UFUNCTION(BlueprintCallable)
	void MiddleBossDamaged(float damage);

	// ���� �ƿ� �����°� BTTask���� �ϰ�
	UFUNCTION(BlueprintCallable)
	void SetIsGuarding(bool isGuarding);

	
private:

	// �÷��̾�
	UPROPERTY()
	class AActor* player;

	void Attack();

	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = AttackSkill, Meta=(AllowPrivateAccess = true))
	bool IsAttacking;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = AttackSkill, Meta = (AllowPrivateAccess = true))
	bool IsGuarding;

	// ���� �����ߴ��� �Ǵ��ϴ� ����(BT Decorator��)
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = AttackSkill, Meta = (AllowPrivateAccess = true))
	bool IsGuardSuccess;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = AttackSkill, Meta = (AllowPrivateAccess = true))
	bool IsShockWaving;

	// �⿭�� ���������� �Ǵ��ϴ� ����
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = AttackSkill, Meta = (AllowPrivateAccess = true))
	bool IsGuardSuccessing;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = AttackSkill, Meta = (AllowPrivateAccess = true))
	float GuardingDamage;

	// ���������� �Ǵ�
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attacked, Meta = (AllowPrivateAccess = true))
	bool IsHitStuning;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attacked, Meta = (AllowPrivateAccess = true))
	float CounterDamage = 30.0f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Moving, Meta = (AllowPrivateAccess = true))
	class UCharacterMovementComponent* movementComp;


	// �⿭��
	void GuardSuccess();

	// ���� �����
	void ShockWave();

	// ����
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

	virtual bool GetAIGuardingSuccess() override;
	virtual bool GetAIGuarding() override;

	virtual void SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished) override;
	virtual void SetAIShockWaveDelegate(const FAICharacterShockWaveFinished& InOnShockWaveFinished) override;
	virtual void AttackByAI() override;
	virtual void ShockWaveByAI() override;
	virtual void GuardSuccessByAI() override;

	virtual void SpeedChangeByAI(float Speed) override;

	// ���޹��� ��������Ʈ�� �����ϴ� �Լ�
	FAICharacterAttackFinished OnAttackFinished;
	FAICharacterShockWaveFinished OnShockWaveFinished;
};

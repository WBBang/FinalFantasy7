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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* dummyCubeMesh;

	// 기본 공격 Collision
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* rightHandComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* leftHandComp;
	
	// 기본 공격 충돌 처리 (Overlap으로만 받아서 몸체랑은 처리안하게)
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	void SetRightHandCompColl(bool IsColl);
	void SetLeftHandCompColl(bool IsColl);
	
	UPROPERTY(EditAnywhere)
	bool IsDuringAttack;


	// HP Bar
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HPBar)
	TSubclassOf<class AMBHpBarActor> hpBar;

	// HP Bar 레퍼런스 변수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HPBar)
	class AMBHpBarActor* hpBarUI;

	// 게임 클리어 때 부를 액터 공장
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameEvent)
	TSubclassOf<class ALevelTransitionPortal> MoveToFinalBossMapFactory;

	// Guard Bar
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = guardBar)
	TSubclassOf<class AMBGuardBarActor> guardBar;

	// Guard Bar 레퍼런스 변수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = guardBar)
	class AMBGuardBarActor* guardBarUI;

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
	void MiddleBossDamagedByBasicBullet(int32 damage);
	
	// 플레이어에게 스킬 공격으로 맞은 경우
	UFUNCTION()
	void MiddleBossDamagedBySkillBullet(int32 damage);
	
	// 공격 당함
	UFUNCTION(BlueprintCallable)
	void MiddleBossDamaged(int32 damage);

	// 가드 아예 끝나는거 BTTask에서 하게
	UFUNCTION(BlueprintCallable)
	void SetIsGuarding(bool isGuarding);

	// Camera Shake - 지면 충격파
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackSkill)
	TSubclassOf<UCameraShakeBase> CSShockWave;

	
private:

	// 플레이어
	UPROPERTY()
	class AActor* player;

	void Attack();

	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = AttackSkill, Meta=(AllowPrivateAccess = true))
	bool IsAttacking;

	// 가드 확률 터졌는지 판단하는 변수(BT Decorator용)
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = AttackSkill, Meta = (AllowPrivateAccess = true))
	bool IsGuardDeco;

	//UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = AttackSkill, Meta = (AllowPrivateAccess = true))
	bool IsGuarding;

	// 가드 성공했는지 판단하는 변수(BT Decorator용)
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = AttackSkill, Meta = (AllowPrivateAccess = true))
	bool IsGuardSuccessDeco;

	// 기열파 실행중인지 판단하는 변수
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = AttackSkill, Meta = (AllowPrivateAccess = true))
	bool IsGuardSuccessing;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = AttackSkill, Meta = (AllowPrivateAccess = true))
	bool IsShockWaving;

	// 경직중인지 판단
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = AttackSkill, Meta = (AllowPrivateAccess = true))
	bool IsHitStuning;


	// 죽어있는지 판단
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Moving, Meta = ( AllowPrivateAccess = true ))
	bool IsDying;
	// Decorator용
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Moving, Meta = ( AllowPrivateAccess = true ))
	bool IsDyingDeco;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = AttackSkill, Meta = ( AllowPrivateAccess = true ))
	int32 GuardingDamage;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = AttackSkill, Meta = ( AllowPrivateAccess = true ))
	int32 CounterDamage = 3;


	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Moving, Meta = (AllowPrivateAccess = true))
	class UCharacterMovementComponent* movementComp;

	// 기열파
	void GuardSuccess();

	// 지면 충격파
	void ShockWave();

	// 가드
	void Guard();

	// 게임 클리어
	void MBGameClear();


	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Moving, Meta = (AllowPrivateAccess = true))
	int32 MiddleBossHP;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Moving, Meta = (AllowPrivateAccess = true))
	int32 MiddleBossMaxHP = 10;

// AI Section
protected:
	virtual float GetAIPatrolRadius() override;
	virtual float GetAIDetectRange() override;
	virtual float GetAIAttackRange() override;
	virtual float GetAISkillRange() override;
	virtual float GetAITurnSpeed() override;

	virtual bool GetAIGuardingSuccess() override;
	virtual bool GetAIGuarding() override;
	virtual bool GetAIDying() override;

	virtual void SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished) override;
	virtual void SetAIShockWaveDelegate(const FAICharacterShockWaveFinished& InOnShockWaveFinished) override;
	virtual void AttackByAI() override;
	virtual void ShockWaveByAI() override;
	virtual void GuardByAI() override;
	virtual void GuardSuccessByAI() override;
	virtual void DieByAI() override;

	virtual void SpeedChangeByAI(float Speed) override;

	// 전달받은 델리게이트를 보관하는 함수
	FAICharacterAttackFinished OnAttackFinished;
	FAICharacterShockWaveFinished OnShockWaveFinished;
};

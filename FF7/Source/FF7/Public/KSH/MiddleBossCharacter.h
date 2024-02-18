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



	// ----------------------- 컴포넌트 -----------------------
private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Moving, Meta = ( AllowPrivateAccess = true ))
	class UCharacterMovementComponent* movementComp;

public: 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* skeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* dummyCubeMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = guard)
	class UStaticMeshComponent* ShieldComp;									// Guard시 나오는 쉴드

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



	// ----------------------- 플레이어 관련 -----------------------
private:
	UPROPERTY()
	class AActor* player;

	
public:
	UFUNCTION()
	void MiddleBossDamagedByBasicBullet(int32 damage);						// 플레이어에게 기본 공격으로 맞은 경우

	UFUNCTION()
	void MiddleBossDamagedBySkillBullet(int32 damage);						// 플레이어에게 스킬 공격으로 맞은 경우

	UFUNCTION(BlueprintCallable)
	void MiddleBossDamaged(int32 damage);									// 공격 당하면 무조건 호출하는 함수
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<class AMBDamageTextUI> MBDamageTextUI;						// 공격 당하면 나오는 데미지

	UFUNCTION()
	void MiddleBossDamagedText(int32 AttackType, int32 damage);				// 공격 당하면 데미지 출력하는 함수


	// ----------------------- 중간 보스 -----------------------
private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Moving, Meta = ( AllowPrivateAccess = true ))
	int32 MiddleBossHP;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Moving, Meta = ( AllowPrivateAccess = true ))
	int32 MiddleBossMaxHP = 100;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = UI, Meta = ( AllowPrivateAccess = true ))
	class AMBHpBarActor* hpBarUI;											// HP Bar 레퍼런스 변수

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = UI, Meta = ( AllowPrivateAccess = true ))
	class AMBNameActor* MBNameUI;											// 이름 UI 레퍼런스 변수

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = UI, Meta = ( AllowPrivateAccess = true ))
	class AMBGuardBarActor* guardBarUI;										// Guard Bar 레퍼런스 변수

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = UI, Meta = ( AllowPrivateAccess = true ))
	class AMBSkillNameActor* MBSkillNameUI;									// 스킬명 UI 레퍼런스 변수

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = UI, Meta = ( AllowPrivateAccess = true ))
	FString SkillName;														// 스킬명

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<class AMBHpBarActor> hpBar;									// HP Bar

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<class AMBNameActor> MBName;									// 이름 UI

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<class AMBGuardBarActor> guardBar;							// Guard Bar

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<class AMBSkillNameActor> MBSkillName;						// 스킬명 UI



	// ----------------------- 애니메이션 -----------------------
private:
	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

public:



	// ----------------------- 평타 -----------------------
private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = AttackSkill, Meta = ( AllowPrivateAccess = true ))
	bool IsAttacking;

	void Attack();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* rightHandComp;									// 오른손 Collision

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* leftHandComp;									// 왼손 Collision
	
	UPROPERTY(EditAnywhere)
	bool IsDuringAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackSkill)
	float canAttackRange;													// 평타 범위

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackSkill)
	TSubclassOf<UCameraShakeBase> CSAttack;									// Camera Shake - 평타

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;		// 기본 공격 충돌 처리 (Overlap으로만 받아서 몸체랑은 처리안하게)
	void SetRightHandCompColl(bool IsColl);
	void SetLeftHandCompColl(bool IsColl);
	


	// ----------------------- 스킬 ----------------------- 
private:

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackSkill)
	float canSkillRange;													// 스킬 범위



	// ----------------------- 가드 ----------------------- 
private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = AttackSkill, Meta = ( AllowPrivateAccess = true ))
	int32 GuardStartTempDamage = 0;											// 가드 시작하는지 판단 누적 데미지

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = AttackSkill, Meta = ( AllowPrivateAccess = true ))
	int32 GuardStartDamage = 15;											// 가드 시작하는 데미지

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = AttackSkill, Meta = ( AllowPrivateAccess = true ))
	int32 GuardingDamage;													// 가드 중일 때 누적되는 데미지

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = AttackSkill, Meta = ( AllowPrivateAccess = true ))
	int32 GuardColorChangeDamage = 8;										// 가드 색 변하는 데미지

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = AttackSkill, Meta = ( AllowPrivateAccess = true ))
	int32 CounterDamage = 10;												// 가드 카운터되는 데미지

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = AttackSkill, Meta = (AllowPrivateAccess = true))
	bool IsGuardDeco;														// 가드 시작인지 판단하는 변수(BT Decorator용)

	//UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = AttackSkill, Meta = (AllowPrivateAccess = true))
	bool IsGuarding;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = AttackSkill, Meta = ( AllowPrivateAccess = true ))
	class UMaterial* shieldMatBlue;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = AttackSkill, Meta = ( AllowPrivateAccess = true ))
	class UMaterial* shieldMatRed;

	void Guard();															// 가드

public:
	UFUNCTION(BlueprintCallable)
	void SetIsGuarding(bool isGuarding);									// 가드 아예 끝나는거 BTTask에서 하게


	// ----------------------- 가드 성공 ----------------------- 
private:
	// 가드 성공했는지 판단하는 변수(BT Decorator용)
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = AttackSkill, Meta = ( AllowPrivateAccess = true ))
	bool IsGuardSuccessDeco;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = AttackSkill, Meta = ( AllowPrivateAccess = true ))
	bool IsGuardSuccessing;													// 기열파 실행중인지 판단 변수

	void GuardSuccess();													// 기열파

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackSkill)
	TSubclassOf<class AGuardSuccessAOE> aoeActor;							// 기열파 장판

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackSkill)
	TSubclassOf<class AShockWaveAOE> shockWaveActor;						// 지면 충격파 불덩이

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackSkill)
	TSubclassOf<UCameraShakeBase> CSShockWave;								// Camera Shake - 지면 충격파



	// ----------------------- 지면 충격파 ----------------------- 
private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = AttackSkill, Meta = (AllowPrivateAccess = true))
	bool IsShockWaving;

	void ShockWave(); 														// 지면 충격파

public:



	// ----------------------- 죽기 ----------------------- 
private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Moving, Meta = ( AllowPrivateAccess = true ))
	bool IsDying;															// 죽어있는지 판단
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Moving, Meta = ( AllowPrivateAccess = true ))
	bool IsDyingDeco;														// Decorator용

public:



	// ----------------------- 게임 이벤트 ----------------------- 
private:
	void MBGameClear();														// 게임 클리어

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameEvent)
	TSubclassOf<class ALevelTransitionPortal> MoveToFinalBossMapFactory;	// 게임 클리어 때 부를 액터 공장

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameEvent)
	TSubclassOf<class AMBFloor> MiddleBossFloor;							// 게임 클리어 시 사라지는 바닥



	// ----------------------- AI ----------------------- 
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

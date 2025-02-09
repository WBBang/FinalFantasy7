﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Barrett.generated.h"

// 이동상태, 공격상태 애니메이션
UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	Walking UMETA(DisplayName = "Walking"),
	Aiming UMETA(DisplayName = "Aiming"),
};

UCLASS()
class FF7_API ABarrett : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABarrett();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	UFUNCTION(BlueprintCallable)
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	//////////////////////// 컴포넌트 ////////////////////////
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpringArmComponent* springArmComp;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UCameraComponent* cameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCharacterMovementComponent* movementComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector direction;

	UFUNCTION(BlueprintCallable)
	void Move();
	 

	//////////////////////// 이동 ////////////////////////
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool W = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool A = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool S = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool D = false;

	//////////////////////// 스킬 ////////////////////////
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsSkill = false;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCameraShakeBase> WangBBang;
	UPROPERTY(EditAnywhere)
	int32 BarrettMaxSkill = 10;
	UPROPERTY(EditAnywhere)
	int32 BarrettSkill = 0;
	UPROPERTY(EditAnywhere)
	float SkillCurTime = 0;
	UPROPERTY(EditAnywhere)
	float AutoRestoreTime = 1.5f;


	////////////////////////// 기본 공격 //////////////////////////
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool autofire = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsFire = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsAttacking = true;

	UFUNCTION(BlueprintCallable)
	void StartAttack();
	UFUNCTION(BlueprintCallable)
	void EndAttack();
	UFUNCTION(BlueprintCallable)
	void Fire();
	UFUNCTION(BlueprintCallable)
	void EnergyFire();

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCameraShakeBase> Basic;


	////////////////////////// 락온 ////////////////////////
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Tab = false;


	////////////////////////// 구르기 //////////////////////////
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool SpaceBar = false;
	void OnActionRoll();
	int64 milliseconds;


	////////////////////////// 스프린트 //////////////////////////
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool LeftShift = false;


	////////////////////////// Player 시점 //////////////////////////
	UFUNCTION(BlueprintCallable)
	void OnAxisVertical(float value);
	UFUNCTION(BlueprintCallable)
	void OnAxisHorizontal(float value);
	void OnAxisTurnYaw(float value);
	void OnAxisLookupPitch(float value);
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* RifleMeshComp;
	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* playerMeshComp;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABulletActor> bulletFactory;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABullet_Energy> energyFactory;


	////////////////////////// 공격 당함 //////////////////////////
	UPROPERTY(EditAnywhere)
	int32 BarrettMaxHP = 300;
	UPROPERTY(EditAnywhere)
	int32 BarrettHP = BarrettMaxHP;
	UPROPERTY(EditAnywhere)
	bool IsAttacked = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsCountered = false;

	UPROPERTY(EditAnywhere)
	bool IsDie = false;


	UFUNCTION(BlueprintCallable)
	void BarrettDamaged(int32 damage);
	UFUNCTION(BlueprintCallable)
	void BarrettDamagedKnockBack(int32 damage);
	UFUNCTION(BlueprintCallable)
	void BarrettDamagedLittleKnockBack();


	
	UPROPERTY(EditAnywhere,BlueprintReadWrite) 
	class UParticleSystem* sparkle;            // 우와앙빵 파티클
	UPROPERTY(EditAnywhere,BlueprintReadWrite) 
	class UParticleSystem* boom;
	UPROPERTY(EditAnywhere,BlueprintReadWrite) 
	class UParticleSystem* basicAttackEnd;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Damage = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurFireTime = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxFireTime = 0.1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackEndTime = 0;


	//////////////////////// 카메라 락온 ////////////////////////
	UFUNCTION()
	void LockOn();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsTargetLocked = false;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class AActor* HitActor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TEnumAsByte<EObjectTypeQuery>> LockOnArea;
	UPROPERTY(BlueprintReadOnly, Category = "CharacterState")
	ECharacterState CharacterState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	bool bIsLockOn = false;
	UFUNCTION()
	void LockOff();


	//////////////////////// 몽타주 ////////////////////////
	UPROPERTY(EditAnywhere)
	class UAnimMontage* rollMontage;
	UPROPERTY(EditAnywhere)
	class UAnimMontage* BasicAttackMontage;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* SkillAttackMontage;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* DieMontage;
	UPROPERTY(EditAnywhere)
	class UAnimMontage* CounterHitMontage;
	UPROPERTY(EditAnywhere)
	class UAnimMontage* HitMontage;
	UPROPERTY(EditAnywhere)
	class UAnimMontage* StandUpMontage;

	/*void PlayMontage(UAnimMontage* NewMontage);*/

	//////////////////////// Sound ////////////////////////

	UPROPERTY(EditAnywhere)
	class USoundBase* fireSound;
	UPROPERTY(EditAnywhere)
	class USoundBase* energyfireSound;
	UPROPERTY(EditAnywhere)
	class USoundBase* energyChargingfireSound;

	UPROPERTY(EditAnywhere)
	class USoundBase* hitSound;
	UPROPERTY(EditAnywhere)
	class USoundBase* counteredSound;

	//////////////////////// Barrett Widget////////////////////////
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget>HPUIFactory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBarretHPWidget* BarretUI;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> GameOverWidgetFactory;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBarrettGameOverWidget* GameOverUI;
};

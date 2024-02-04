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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AGuardSuccessAOE> aoeActor;

	// 지면 충격파 불덩이
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AShockWaveAOE> shockWaveActor;

private:

	// 플레이어
	UPROPERTY()
	class AActor* player;

	void Attack();

	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta=(AllowPrivateAccess = true))
	bool IsAttacking;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Guard, Meta = (AllowPrivateAccess = true))
	bool IsGuarding;


	// 기열파
	void GuardSuccess();

	// 지면 충격파
	void ShockWave();

	// 가드
	void Guard();

// AI Section
protected:
	virtual float GetAIPatrolRadius() override;
	virtual float GetAIDetectRange() override;
	virtual float GetAIAttackRange() override;
	virtual float GetAITurnSpeed() override;

	virtual void SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished) override;
	virtual void AttackByAI() override;

	// 전달받은 델리게이트를 보관하는 함수
	FAICharacterAttackFinished OnAttackFinished;

};

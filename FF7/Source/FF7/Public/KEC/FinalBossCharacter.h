// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FinalBossCharacter.generated.h"


UCLASS()
class FF7_API AFinalBossCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFinalBossCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* leftArrowComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* rightArrowComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* missieLaunchArrowComp;
	
	UPROPERTY(EditAnywhere)
	class UParticleSystem* fireVFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UFinalBossFSM* bossFsm;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf <class ABossBullet> bulletFactory;

	UPROPERTY(EditAnywhere)
	TSubclassOf <class AMissile> missileFactory;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 fireCount = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float playerLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float jumpSpeed = 300;
	
	bool bIsJumpAttack = true;
	bool isDetected = true;
	int32 fireNum = 0;
	

	void Fire();
	void LauchMissile();
	void RushAttack();
	void AttackLength();
	
};

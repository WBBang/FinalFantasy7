// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FinalBossFSM.generated.h"

UENUM(BlueprintType)
enum class EFinalBossState : uint8
{
	IDLE			UMETA(DisplayName = "IDLE"),
	MOVE			UMETA(DisplayName = "MOVE"),
	NORMALATTACK	UMETA(DisplayName = "NORMALATTACK"),
	FireMissile		UMETA(DisplayName = "FIREMISSILE"),
	LAUNCHBOMB		UMETA(DisplayName = "LAUNCHBOMB"),
	RUSH			UMETA(DisplayName = "RUSH"),
	JUMPATTACK		UMETA(DisplayName = "JUMPATTACK"),
	GROGGY			UMETA(DisplayName = "GROGGY"),
	DEAD			UMETA(DisplayName = "DEAD")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FF7_API UFinalBossFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFinalBossFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EFinalBossState state;

	UPROPERTY(EditAnywhere)
	class ACharacter* target;
	
	UPROPERTY(EditAnywhere)
	class AFinalBossCharacter* me;

	FVector rushStartVector;
	float attackLength = 500;
	float detectRange = 2000;
	float currentTime;
	float normalAttackCooldown = 2;
	float rushSpeed = 3000;
	float rushingTime = 1;

	int normalAttackCount;
	

	void TickIdle();
	void TickMove();
	void TickNormalAttack();	
	void TickFireMissile();	
	void TickLaunchBomb();	
	void TickRush();
	void TickJumpAttack();
	void TickGroggy();	
	void TickDead();

	void SetState(EFinalBossState next);
};

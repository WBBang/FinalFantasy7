// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Barrett.generated.h"

// �̵�����, ���ݻ��� �ִϸ��̼�
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


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpringArmComponent* springArmComp;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UCameraComponent* cameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector direction;

	UFUNCTION(BlueprintCallable)
	void Move();
	 

	// �̵� Ű Bool
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool W = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool A = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool S = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool D = false;

	// ���� Ű Bool
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsFire;

	// ��ų Ű Bool
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsSkill;

	// ���� Ű Bool
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Tab = false;

	// ������ Ű Bool
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool SpaceBar = false;

	// ������Ʈ Ű Bool
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool LeftShift = false;

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

	// Auto Fire 
	int Damage = 0;
	float CurFireTime = 0;
	float MaxFireTime = 0.1;


	UFUNCTION()
	void StartAttack();
	UFUNCTION()
	void EndAttack();

	void Fire();
	void EnergyFire();

	void LineTrace();
	bool bIsAttacking = false;


	// Camera Lock On
	UFUNCTION()
	void LockOn();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsTargetLocked = false;

	class AActor* HitActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TEnumAsByte<EObjectTypeQuery>> LockOnArea;


	UPROPERTY(BlueprintReadOnly, Category = "CharacterState")
	ECharacterState CharacterState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    bool bIsLockOn = false;


	void OnActionRoll();
	UPROPERTY(EditAnywhere)
	class UAnimMontage* rollMontage;

	int64 milliseconds;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Barrett.generated.h"

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
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditAnywhere)
	class USpringArmComponent* springArmComp;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UCameraComponent* cameraComp;

	FVector direction;

	void Move();

	void OnAxisVertical(float value);

	void OnAxisHorizontal(float value);

	void OnAxisTurnYaw(float value);
	void OnAxisLookupPitch(float value);


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* RifleMeshComp;

	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* playerMeshComp;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABulletActor> bulletFactory;

	int Damage;
	float CurFireTime;
	float MaxFireTime = 0.1;
	bool IsFire;

	UFUNCTION()
	void StartAttack();
	UFUNCTION()
	void EndAttack();

	void Fire();

	void LineTrace();
	bool bIsAttacking;

};

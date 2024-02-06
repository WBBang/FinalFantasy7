// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Missile.generated.h"

UCLASS()
class FF7_API AMissile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMissile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(EditAnywhere)
	class AMissile* missile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* skeletalMeshComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* capsuleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNiagaraComponent* MissileNiagara;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float impuslePos = 50000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float missileSpeed = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float delayTime = 1.5f;
	

	void LaunchMissile();
	void CruiseMissile();
	void SetRotation();
	

	UPROPERTY(EditAnywhere)
	FVector playerPosition;

	UPROPERTY(EditAnywhere)
	FRotator playerRotate;

	UPROPERTY(EditAnywhere)
	FVector targetDir;

	UPROPERTY(EditAnywhere)
	bool isRotating;
};

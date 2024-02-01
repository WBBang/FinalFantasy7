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
	class UCapsuleComponent* capsuleComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float impuslePos = 50000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float missileSpeed = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float delayTime = 3.0f;

	bool cruiseReady = false;

	void LaunchMissile();
	void CruiseMissile();
	
	void Delay();

	UPROPERTY(EditAnywhere)
	FVector playerPosition;

	UPROPERTY(EditAnywhere)
	FVector targetPosition;

	UPROPERTY(EditAnywhere)
	bool isLaunched;

	
};

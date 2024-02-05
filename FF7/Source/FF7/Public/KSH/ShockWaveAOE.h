// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShockWaveAOE.generated.h"

UCLASS()
class FF7_API AShockWaveAOE : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShockWaveAOE();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// 플레이어
	UPROPERTY()
	class AActor* player;

	// 현재 시간
	float currentTime;

	// 추격 시간
	float chaseTime = 2;

	// 사라지는 시간
	float distroyTime = 3;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 이동 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float speed = 1000.0f;

	// 따라오는 불덩이
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystemComponent* ShockWaveFire;

	// 충돌체
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* sphereComp;
};

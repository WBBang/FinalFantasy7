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
	// �÷��̾�
	UPROPERTY()
	class AActor* player;

	// ���� �ð�
	float currentTime;

	// �߰� �ð�
	float chaseTime = 2;

	// ������� �ð�
	float distroyTime = 3;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// �̵� �ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float speed = 1000.0f;

	// ������� �ҵ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystemComponent* ShockWaveFire;

	// �浹ü
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* sphereComp;
};

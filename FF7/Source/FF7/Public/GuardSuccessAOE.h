// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GuardSuccessAOE.generated.h"

UCLASS()
class FF7_API AGuardSuccessAOE : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGuardSuccessAOE();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// ó�� ���� - �ѹ� ������ �����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystemComponent* pFireFirst;

	// ��� (�� ��ƼŬ 4��) - ���� ������� ���� ���� (�÷��̾� ���� ������ ����)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystemComponent* pFirePillar0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystemComponent* pFirePillar1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystemComponent* pFirePillar2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystemComponent* pFirePillar3;

	// ��� ������ �Լ�
	void ActiveFirePillar();

	UFUNCTION()
	void OnEffectFinished(UParticleSystemComponent* PSystem);
};

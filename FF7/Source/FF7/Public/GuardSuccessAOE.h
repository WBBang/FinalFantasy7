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

	// 충돌체
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent*boxComp;

	// 처음 장판 - 한번 터지고 사라짐
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystemComponent* pFireFirst;

	// 기둥 (불 파티클 4개) - 장판 사라지고 나서 등장 (플레이어 위로 보내는 공격)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystemComponent* pFirePillar0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystemComponent* pFirePillar1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystemComponent* pFirePillar2;

	// 기둥 나오는 함수
	void ActiveFirePillar();

	UFUNCTION()
	void OnEffectFinished(UParticleSystemComponent* PSystem);
};

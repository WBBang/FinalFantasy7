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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 따라오는 불덩이
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystemComponent* ShockWaveFire;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FinalBoss.generated.h"

UCLASS()
class FF7_API AFinalBoss : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFinalBoss();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* firePosition;

	void SpawnMissile();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AMissile> missile;
	
};

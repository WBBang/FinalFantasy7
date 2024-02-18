// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelTransitionPortal.generated.h"

UCLASS()
class FF7_API ALevelTransitionPortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelTransitionPortal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UParticleSystem* portalParticle;
	
	UPROPERTY(EditAnywhere)
	FName transferLevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* levelTransitionPortal;

};

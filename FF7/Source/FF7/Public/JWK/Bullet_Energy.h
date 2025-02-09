﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet_Energy.generated.h"

UCLASS()
class FF7_API ABullet_Energy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet_Energy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//////////////////////// 컴포넌트 ////////////////////////
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BBB")
	class USphereComponent* sphereComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BBB")
	class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BBB")
	class UProjectileMovementComponent* movementComp;


	//////////////////////// 타겟 ////////////////////////
	UPROPERTY()
	class AMiddleBossCharacter* mbcharacter;
	UPROPERTY()
	class AFinalBossCharacter* finalCharacter;


	//////////////////////// 총알 ////////////////////////
	FORCEINLINE void AutoDestroy() { this->Destroy(); }
	//UFUNCTION()
	//void OnMyCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// 충돌 처리
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};

﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MBDamageTextUI.generated.h"

UCLASS()
class FF7_API AMBDamageTextUI : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMBDamageTextUI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// ------------ 컴포넌트 ------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTextRenderComponent* textRender;

	// ------------ 데미지 ------------
	UFUNCTION(BlueprintCallable)
	void SetDamageText(int32 AttackType, int32 Damage);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FinalBossFSM.h"
#include "Animation/AnimInstance.h"
#include "FinalBossAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FF7_API UFinalBossAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EFinalBossState state;
	
};

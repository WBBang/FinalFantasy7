// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ShockWave.generated.h"

/**
 * 
 */
UCLASS()
class FF7_API UBTTask_ShockWave : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_ShockWave();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};

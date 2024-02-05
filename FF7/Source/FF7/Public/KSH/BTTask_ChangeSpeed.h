// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ChangeSpeed.generated.h"

/**
 * 이동 속도 바꾸는 Task
 */
UCLASS()
class FF7_API UBTTask_ChangeSpeed : public UBTTaskNode
{
	GENERATED_BODY()

	protected:
    // 속도
    UPROPERTY(EditAnywhere, Category = "Speed")
    float Speed;
	
public:
	UBTTask_ChangeSpeed();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

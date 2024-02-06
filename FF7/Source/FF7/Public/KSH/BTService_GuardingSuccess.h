// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_GuardingSuccess.generated.h"

/**
 * 
 */
UCLASS()
class FF7_API UBTService_GuardingSuccess : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_GuardingSuccess();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};

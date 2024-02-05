// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_SkillInRange.generated.h"

/**
 * 
 */
UCLASS()
class FF7_API UBTDecorator_SkillInRange : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_SkillInRange();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMememory) const override;
	
};

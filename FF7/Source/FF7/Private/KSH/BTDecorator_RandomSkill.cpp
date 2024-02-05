// Fill out your copyright notice in the Description page of Project Settings.


#include "KSH/BTDecorator_RandomSkill.h"
#include "KSH/MBAI.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "KSH/MBCharacterAIInterface.h"

UBTDecorator_RandomSkill::UBTDecorator_RandomSkill()
{
	NodeName = TEXT("SelectRandomSkill");
}

bool UBTDecorator_RandomSkill::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMememory) const
{
	int RandomNum = FMath::RandRange(0, 1);
	if (RandomNum == 0) return false;
	else if (RandomNum == 1) return true;

	return false;
}

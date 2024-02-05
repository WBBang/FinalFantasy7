// Fill out your copyright notice in the Description page of Project Settings.


#include "KSH/BTDecorator_SkillInRange.h"
#include "KSH/MBCharacterAIInterface.h"
#include "KSH/MBAI.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_SkillInRange::UBTDecorator_SkillInRange()
{
	NodeName = TEXT("CanSkill");
}

bool UBTDecorator_SkillInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMememory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMememory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return false;
	}

	IMBCharacterAIInterface* AIPawn = Cast<IMBCharacterAIInterface>(ControllingPawn);
	if (nullptr == AIPawn)
	{
		return false;
	}

	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGET));
	if (nullptr == Target)
	{
		return false;
	}

	// 거리 구하기
	float DistanceToTarget = ControllingPawn->GetDistanceTo(Target);
	// AI에서 판단한 스킬 범위 내에
	float SkillRangeWithRadius = AIPawn->GetAISkillRange();
	// 지금 거리가 들어오면 true 반환
	bResult = (DistanceToTarget <= SkillRangeWithRadius);
	return bResult;

	return false;
}

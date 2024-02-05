// Fill out your copyright notice in the Description page of Project Settings.


#include "KSH/BTDecorator_AttackInRange.h"
#include "KSH/MBAI.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "KSH/MBCharacterAIInterface.h"

UBTDecorator_AttackInRange::UBTDecorator_AttackInRange()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_AttackInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMememory) const
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
	// AI에서 판단한 공격범위 내에
	float AttackRangeWithRadius = AIPawn->GetAIAttackRange();
	// 지금 거리가 들어오면 true 반환
	bResult = (DistanceToTarget <= AttackRangeWithRadius);
	return bResult;
}

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

	// �Ÿ� ���ϱ�
	float DistanceToTarget = ControllingPawn->GetDistanceTo(Target);
	// AI���� �Ǵ��� ���ݹ��� ����
	float AttackRangeWithRadius = AIPawn->GetAIAttackRange();
	// ���� �Ÿ��� ������ true ��ȯ
	bResult = (DistanceToTarget <= AttackRangeWithRadius);
	return bResult;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "KSH/BTTask_GuardSuccess.h"
#include "AIController.h"
#include "KSH/MBCharacterAIInterface.h"

UBTTask_GuardSuccess::UBTTask_GuardSuccess()
{
}

EBTNodeResult::Type UBTTask_GuardSuccess::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}

	IMBCharacterAIInterface* AIPawn = Cast<IMBCharacterAIInterface>(ControllingPawn);
	if (nullptr == AIPawn)
	{
		return EBTNodeResult::Failed;
	}

	FAICharacterAttackFinished OnAttackFinished;
	OnAttackFinished.BindLambda(
		[&]()
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	);
	AIPawn->SetAIAttackDelegate(OnAttackFinished);
	AIPawn->GuardSuccessByAI();
	return EBTNodeResult::InProgress;
}

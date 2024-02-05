// Fill out your copyright notice in the Description page of Project Settings.


#include "KSH/BTTask_ChangeSpeed.h"
#include "AIController.h"
#include "KSH/MBCharacterAIInterface.h"

UBTTask_ChangeSpeed::UBTTask_ChangeSpeed()
{
	Speed = 0.0f;
}

EBTNodeResult::Type UBTTask_ChangeSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	AIPawn->SpeedChangeByAI(Speed);
	return EBTNodeResult::Succeeded;
}

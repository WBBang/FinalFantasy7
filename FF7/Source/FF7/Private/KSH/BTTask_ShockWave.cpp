// Fill out your copyright notice in the Description page of Project Settings.


#include "KSH/BTTask_ShockWave.h"
#include "AIController.h"
#include "KSH/MBCharacterAIInterface.h"

UBTTask_ShockWave::UBTTask_ShockWave()
{
}

EBTNodeResult::Type UBTTask_ShockWave::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	//FAICharacterAttackFinished OnAttackFinished;
	FAICharacterShockWaveFinished OnShockWaveFinished;

	OnShockWaveFinished.BindLambda(
		[&]()
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	);
	AIPawn->SetAIShockWaveDelegate(OnShockWaveFinished);
	AIPawn->ShockWaveByAI();
	return EBTNodeResult::InProgress;
}

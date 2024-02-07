// Fill out your copyright notice in the Description page of Project Settings.


#include "KSH/BTTask_TurnToTarget.h"
#include "KSH/MBAIController.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "KSH/MiddleBossCharacter.h"
#include "KSH/MBAI.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
	NodeName = TEXT("Turn");
}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto MBCharacter = Cast<AMiddleBossCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == MBCharacter) return EBTNodeResult::Failed;

	auto Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target"))));
	if ( nullptr == Target ) {
		UE_LOG(LogTemp, Log, TEXT("Fail Find Target"));
		return EBTNodeResult::Failed;
	}

	FVector LookVector = Target->GetActorLocation() - MBCharacter->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	MBCharacter->SetActorRotation(FMath::RInterpTo(MBCharacter->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));

	return EBTNodeResult::Succeeded;
}

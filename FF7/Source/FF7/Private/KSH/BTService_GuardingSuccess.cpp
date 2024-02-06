// Fill out your copyright notice in the Description page of Project Settings.


#include "KSH/BTService_GuardingSuccess.h"
#include "KSH/MBAI.h"
#include "AIController.h"
#include "KSH//MBCharacterAIInterface.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Engine/OverlapResult.h"
#include "../../../../../../../Source/Runtime/Engine/Public/CollisionQueryParams.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Engine/World.h"
#include "../../../../../../../Source/Runtime/PhysicsCore/Public/CollisionShape.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/Pawn.h"

UBTService_GuardingSuccess::UBTService_GuardingSuccess()
{
	NodeName = TEXT("GuardSuccess");
	Interval = 1.0f;
}

void UBTService_GuardingSuccess::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return;
	}

	FVector Center = ControllingPawn->GetActorLocation();
	UWorld* World = ControllingPawn->GetWorld();
	if (nullptr == World)
	{
		return;
	}

	IMBCharacterAIInterface* AIPawn = Cast<IMBCharacterAIInterface>(ControllingPawn);
	if (nullptr == AIPawn)
	{
		return;
	}

	bool IsGuardSuccessing = AIPawn->GetAIGuardingSuccess();
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(BBKEY_ISGUARDSUCCESS, IsGuardSuccessing);
	if(IsGuardSuccessing)
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, TEXT("IsGuardSuccess")); // 게임 화면
	else GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, TEXT("NotSuccess")); // 게임 화면
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "KSH/BTService_IsGuarding.h"
#include "KSH/MBAI.h"
#include "AIController.h"
#include "KSH//MBCharacterAIInterface.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Engine/OverlapResult.h"
#include "../../../../../../../Source/Runtime/Engine/Public/CollisionQueryParams.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Engine/World.h"
#include "../../../../../../../Source/Runtime/PhysicsCore/Public/CollisionShape.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/Pawn.h"

UBTService_IsGuarding::UBTService_IsGuarding()
{
	NodeName = TEXT("Guard");
	Interval = 1.0f;
}

void UBTService_IsGuarding::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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

	bool IsGuarding = AIPawn->GetAIGuarding();
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(BBKEY_ISGUARDING, IsGuarding);
	if (IsGuarding)
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, TEXT("IsGuarding")); // 게임 화면
	else GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, TEXT("IsNotGuarding")); // 게임 화면
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "KSH/MBAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "KSH/MBAI.h"
#include "KSH/MiddleBossCharacter.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"

AMBAIController::AMBAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBAssetRef(TEXT("/Script/AIModule.BlackboardData'/Game/KSH/AI/BB_MiddleBoss.BB_MiddleBoss'"));
	if (nullptr != BBAssetRef.Object)
	{
		BBAsset = BBAssetRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAssetRef(TEXT("/Script/AIModule.BehaviorTree'/Game/KSH/AI/BT_MiddleBoss.BT_MiddleBoss'"));
	if (nullptr != BTAssetRef.Object)
	{
		BTAsset = BTAssetRef.Object;
	}
}

void AMBAIController::RunAI()
{
	
	//AMiddleBossCharacter* middleBoss = Cast< AMiddleBossCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AMiddleBossCharacter::StaticClass()));
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();
	if (UseBlackboard(BBAsset, BlackboardPtr))
	{
		Blackboard->SetValueAsVector(BBKEY_HOMEPOS, GetPawn()->GetActorLocation());
		//if (middleBoss)
		//	Blackboard->SetValueAsObject(BBKEY_MIDDLEBOSS, middleBoss);
		bool RunResult = RunBehaviorTree(BTAsset);
		ensure(RunResult);
	}
}

void AMBAIController::StopAI()
{
	UBehaviorTreeComponent* BTComponent = Cast <UBehaviorTreeComponent>(BrainComponent);
	if (BTComponent)
	{
		BTComponent->StopTree();
	}
}

void AMBAIController::OnPossess(APawn* InPawn)
{
	// 폰이 빙의했을 때, AI 구동
	Super::OnPossess(InPawn);

	RunAI();
}

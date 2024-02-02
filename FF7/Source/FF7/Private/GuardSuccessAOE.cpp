// Fill out your copyright notice in the Description page of Project Settings.


#include "GuardSuccessAOE.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Engine/TimerHandle.h"
#include "../../../../../../../Source/Runtime/Engine/Public/TimerManager.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Particles/ParticleSystem.h"
#include "../../../../../../../Source/Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

// Sets default values
AGuardSuccessAOE::AGuardSuccessAOE()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 첫 장판
	pFireFirst = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("pFireFirst"));
	SetRootComponent(pFireFirst);
	pFireFirst->SetRelativeScale3D(FVector(0.5));
	ConstructorHelpers::FObjectFinder<UParticleSystem>tempFireFirst(TEXT("/Script/Engine.ParticleSystem'/Game/KSH/ParagonSteel/FX/Particles/Steel/Abilities/Ultimate/FX/P_Steel_Ultimate_Impact.P_Steel_Ultimate_Impact'"));
	if (tempFireFirst.Succeeded())
	{
		pFireFirst->SetTemplate(tempFireFirst.Object);
	}
	
	// 불 기둥
	pFirePillar0 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("pFirePillar0"));
	pFirePillar0->SetupAttachment(RootComponent);
	pFirePillar0->SetRelativeScale3D(FVector(4));
	pFirePillar0->SetRelativeLocation(FVector(0, 0, 0));

	pFirePillar1 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("pFirePillar1"));
	pFirePillar1->SetupAttachment(RootComponent);
	pFirePillar1->SetRelativeScale3D(FVector(4));
	pFirePillar1->SetRelativeLocation(FVector(0, 0, 500));

	pFirePillar2 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("pFirePillar2"));
	pFirePillar2->SetupAttachment(RootComponent);
	pFirePillar2->SetRelativeScale3D(FVector(4));
	pFirePillar2->SetRelativeLocation(FVector(0, 0, 1000));

	pFirePillar0->bAutoActivate = false;
	pFirePillar1->bAutoActivate = false;
	pFirePillar2->bAutoActivate = false;

	ConstructorHelpers::FObjectFinder<UParticleSystem>tempFirePillar(TEXT("/Script/Engine.ParticleSystem'/Game/KSH/FX/Particles/Abilities/Ultimate/FX/P_Burning.P_Burning'"));
	if (tempFirePillar.Succeeded())
	{
		pFirePillar0->SetTemplate(tempFirePillar.Object);
		pFirePillar1->SetTemplate(tempFirePillar.Object);
		pFirePillar2->SetTemplate(tempFirePillar.Object);
	}
}

// Called when the game starts or when spawned
void AGuardSuccessAOE::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle MyTimer;
	float Time = 0.5f;
	GetWorld()->GetTimerManager().SetTimer(MyTimer, FTimerDelegate::CreateLambda([&]()
		{
			ActiveFirePillar();

			// TimerHandle 초기화
			GetWorld()->GetTimerManager().ClearTimer(MyTimer);
		}), Time, false);

	
}

// Called every frame
void AGuardSuccessAOE::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



// 기둥 나오는 함수
void AGuardSuccessAOE::ActiveFirePillar()
{
	UE_LOG(LogTemp, Log, TEXT("HI"));

	pFirePillar0->Activate(true);
	pFirePillar1->Activate(true);
	pFirePillar2->Activate(true);
	//pFirePillar3->OnSystemFinished.AddDynamic(this, &AGuardSuccessAOE::OnEffectFinished);
}

void AGuardSuccessAOE::OnEffectFinished(UParticleSystemComponent* PSystem)
{
	// 마지막 기둥 이펙트 끝나면 장판 3초 뒤에 사라지는 함수
	FTimerHandle MyTimer;
	float Time = 3.0f;
	GetWorld()->GetTimerManager().SetTimer(MyTimer, FTimerDelegate::CreateLambda([&]()
		{
			UE_LOG(LogTemp, Log, TEXT("bye"));
			Destroy();

			// TimerHandle 초기화
			GetWorld()->GetTimerManager().ClearTimer(MyTimer);
		}), Time, false);
}

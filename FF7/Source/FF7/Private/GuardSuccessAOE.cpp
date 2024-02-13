// Fill out your copyright notice in the Description page of Project Settings.


#include "GuardSuccessAOE.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Engine/TimerHandle.h"
#include "../../../../../../../Source/Runtime/Engine/Public/TimerManager.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Particles/ParticleSystem.h"
#include "../../../../../../../Source/Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/BoxComponent.h"
#include "JWK/Barrett.h"

// Sets default values
AGuardSuccessAOE::AGuardSuccessAOE()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 충돌체
	boxComp = CreateDefaultSubobject<UBoxComponent>("boxComp");
	SetRootComponent(boxComp);
	boxComp->SetGenerateOverlapEvents(true);
	boxComp->SetCollisionProfileName(TEXT("EnemyAttack"));
	boxComp->SetBoxExtent(FVector(100, 100, 10));


	// 첫 장판
	pFireFirst = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("pFireFirst"));
	pFireFirst->SetupAttachment(RootComponent);
	//pFireFirst->SetRelativeScale3D(FVector(0.5));
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

	// 불기둥 처음에는 안나오게
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
			// Time 뒤에 불기둥 생성
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

// 플레이어가 맞았다면 하늘로 띄우고 데미지 주기
void AGuardSuccessAOE::NotifyActorBeginOverlap(AActor* OtherActor)
{
	// 충돌한 대상이 플레이어 캐릭터라면
	if ( OtherActor->IsA<ABarrett>() )
	{
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, TEXT("ShockWaveAttack"));
		// 하늘로 띄우기
		ABarrett* player = Cast<ABarrett>(OtherActor);
		player->SetActorLocation(FVector(player->GetActorLocation().X, player->GetActorLocation().Y, player->GetActorLocation().Z+100));
		player->SetActorEnableCollision(false);

		// 하늘로 3초뒤에 내리기
		FTimerHandle MyTimer;
		float Time = 3.0f;
		GetWorld()->GetTimerManager().SetTimer(MyTimer, FTimerDelegate::CreateLambda([ & ] ()
			{
				player->SetActorLocation(FVector(player->GetActorLocation().X, player->GetActorLocation().Y, player->GetActorLocation().Z - 100));
				player->SetActorEnableCollision(true);
				// TimerHandle 초기화
				GetWorld()->GetTimerManager().ClearTimer(MyTimer);
			}), Time, false);

		// 플레이어 데미지 처리하고 넘어지는 함수, 호출

		
	}
}

// 기둥 나오는 함수
void AGuardSuccessAOE::ActiveFirePillar()
{
	pFirePillar0->Activate(true);
	pFirePillar1->Activate(true);
	pFirePillar2->Activate(true);
	pFirePillar2->OnSystemFinished.AddDynamic(this, &AGuardSuccessAOE::OnEffectFinished);
}

void AGuardSuccessAOE::OnEffectFinished(UParticleSystemComponent* PSystem)
{
	// 마지막 기둥 이펙트 끝나면 장판 3초 뒤에 사라지는 함수
	FTimerHandle MyTimer;
	float Time = 3.0f;
	GetWorld()->GetTimerManager().SetTimer(MyTimer, FTimerDelegate::CreateLambda([&]()
		{
			Destroy();

			// TimerHandle 초기화
			GetWorld()->GetTimerManager().ClearTimer(MyTimer);
		}), Time, false);
}
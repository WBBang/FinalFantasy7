// Fill out your copyright notice in the Description page of Project Settings.


#include "KSH/ShockWaveAOE.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Particles/ParticleSystem.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/SphereComponent.h"

// Sets default values
AShockWaveAOE::AShockWaveAOE()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 충돌체
	sphereComp = CreateDefaultSubobject<USphereComponent> ( "sphereComp" );
	SetRootComponent(sphereComp);

	// 불덩이
	ShockWaveFire = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ShockWaveFire"));
	ShockWaveFire->SetupAttachment(RootComponent);
	ShockWaveFire->SetRelativeScale3D(FVector(1));
	ConstructorHelpers::FObjectFinder<UParticleSystem>tempShockWave(TEXT("/Script/Engine.ParticleSystem'/Game/KSH/ParagonSteel/FX/Particles/Steel/Cinematics/FX/P_ShockWave.P_ShockWave'"));
	if (tempShockWave.Succeeded())
	{
		ShockWaveFire->SetTemplate(tempShockWave.Object);
	}
}

// Called when the game starts or when spawned
void AShockWaveAOE::BeginPlay()
{
	Super::BeginPlay();

	// 플레이어 저장
	player = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// Called every frame
void AShockWaveAOE::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 플레이어를 chaseTime동안 쫓다가 chaseTime가 지나면 그냥 직진
	currentTime += DeltaTime;

	FVector P0 = GetActorLocation();
	FVector dir = player->GetActorLocation() - GetActorLocation();

	if (currentTime > chaseTime)
	{
		dir = GetActorForwardVector();
	}
	SetActorLocation(P0 + (dir.GetSafeNormal() * speed * DeltaTime));


	// distroyTime 이상이면 사라지기
	if (currentTime > distroyTime)
	{
		Destroy();
	}
	
}

// 플레이어와 충돌하면 데미지 주고 사라지기


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

	// �浹ü
	sphereComp = CreateDefaultSubobject<USphereComponent> ( "sphereComp" );
	SetRootComponent(sphereComp);

	// �ҵ���
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

	// �÷��̾� ����
	player = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// Called every frame
void AShockWaveAOE::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �÷��̾ chaseTime���� �Ѵٰ� chaseTime�� ������ �׳� ����
	currentTime += DeltaTime;

	FVector P0 = GetActorLocation();
	FVector dir = player->GetActorLocation() - GetActorLocation();

	if (currentTime > chaseTime)
	{
		dir = GetActorForwardVector();
	}
	SetActorLocation(P0 + (dir.GetSafeNormal() * speed * DeltaTime));


	// distroyTime �̻��̸� �������
	if (currentTime > distroyTime)
	{
		Destroy();
	}
	
}

// �÷��̾�� �浹�ϸ� ������ �ְ� �������


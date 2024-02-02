// Fill out your copyright notice in the Description page of Project Settings.


#include "KSH/ShockWaveAOE.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Particles/ParticleSystem.h"

// Sets default values
AShockWaveAOE::AShockWaveAOE()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ∫“µ¢¿Ã
	ShockWaveFire = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ShockWaveFire"));
	SetRootComponent(ShockWaveFire);
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
	
}

// Called every frame
void AShockWaveAOE::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


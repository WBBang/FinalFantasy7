// Fill out your copyright notice in the Description page of Project Settings.


#include "KEC/FinalBoss.h"
#include "KEC/Missile.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/BoxComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/ArrowComponent.h"

// Sets default values
AFinalBoss::AFinalBoss()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	firePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("firePosition"));

	SetRootComponent(boxComp);
	meshComp->SetupAttachment(RootComponent);
	firePosition->SetupAttachment(RootComponent);
	missile = AMissile::StaticClass();
}

// Called when the game starts or when spawned
void AFinalBoss::BeginPlay()
{
	Super::BeginPlay();
	SpawnMissile();
}

// Called every frame
void AFinalBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFinalBoss::SpawnMissile()
{
	FTransform launchLocation = firePosition->GetComponentTransform();
	GetWorld()->SpawnActor<AMissile>(missile, launchLocation);
}


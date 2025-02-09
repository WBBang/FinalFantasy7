﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "KEC/LevelTransitionPortal.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALevelTransitionPortal::ALevelTransitionPortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	levelTransitionPortal = CreateDefaultSubobject<UBoxComponent>(TEXT("levelTransitionPortal"));

	SetRootComponent(levelTransitionPortal);
	levelTransitionPortal->SetBoxExtent(FVector(100));

	levelTransitionPortal->SetCollisionProfileName(TEXT("BarretOnly"));
	
}

// Called when the game starts or when spawned
void ALevelTransitionPortal::BeginPlay()
{
	Super::BeginPlay();

	FRotator rot = FRotator(20, 20, -110);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), portalParticle, GetActorLocation(),rot, FVector(1));
	
}

void ALevelTransitionPortal::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	APawn* pawn = Cast<APawn>(OtherActor);
	if(pawn == GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		UGameplayStatics::OpenLevel(this, transferLevelName);
	}
}

// Called every frame
void ALevelTransitionPortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


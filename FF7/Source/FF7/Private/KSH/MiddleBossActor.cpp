// Fill out your copyright notice in the Description page of Project Settings.


#include "KSH/MiddleBossActor.h"
#include "KSH/MBAIController.h"

// Sets default values
AMiddleBossActor::AMiddleBossActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMiddleBossActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMiddleBossActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Fill out your copyright notice in the Description page of Project Settings.


#include "KSH/Level/MBFloor.h"
#include "KSH/MiddleBossCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMBFloor::AMBFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMBFloor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMBFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMBFloor::MiddleBossGameClear()
{
	UE_LOG(LogTemp, Log, TEXT("Floor Destroy"));
	this->Destroy();
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "KSH/Level/BrokenFloor.h"

// Sets default values
ABrokenFloor::ABrokenFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABrokenFloor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABrokenFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Fill out your copyright notice in the Description page of Project Settings.


#include "KEC/BossBullet.h"

// Sets default values
ABossBullet::ABossBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABossBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABossBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * 30 * GetWorld()->DeltaTimeSeconds);
}


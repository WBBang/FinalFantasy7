// Fill out your copyright notice in the Description page of Project Settings.


#include "KSH/Level/MBFloor.h"
#include "KSH/Level/BrokenFloor.h"
#include "KSH/MiddleBossCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "../../../../../../../Source/Runtime/Experimental/GeometryCollectionEngine/Public/GeometryCollection/GeometryCollectionObject.h"
#include "GeometryCollection/GeometryCollectionActor.h"

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

	FTimerHandle timerHandle;
	GetWorld()->GetTimerManager().SetTimer(timerHandle, FTimerDelegate::CreateLambda([ this ] ()->void {
		FVector loc = FVector(185, 285, 1);
		FRotator rot = FRotator(0, 0, 0);
		GetWorld()->SpawnActor<ABrokenFloor>(brokenFloor, loc, rot);
		if ( nullptr == CSShockWave )return;
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(CSShockWave, 1.0f);
		this->Destroy();
		}), 3, false);
}


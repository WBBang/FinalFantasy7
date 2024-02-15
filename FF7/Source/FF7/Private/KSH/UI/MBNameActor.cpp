// Fill out your copyright notice in the Description page of Project Settings.


#include "KSH/UI/MBNameActor.h"

#include "../../../../../../../Source/Runtime/UMG/Public/Components/WidgetComponent.h"
#include "../../../../../../../Source/Runtime/UMG/Public/Blueprint/UserWidget.h"
// Sets default values
AMBNameActor::AMBNameActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MBNameUI = CreateDefaultSubobject<UWidgetComponent>("MBNameUI");
	MBNameUI->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMBNameActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMBNameActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMBNameActor::UpdateLocation(FVector Location, FRotator Rotator)
{
	this->SetActorLocationAndRotation(Location, Rotator);
}

void AMBNameActor::UpdateScale(float mulTimes)
{
	MBNameUI->SetRelativeScale3D(FVector(0.3f) * mulTimes);
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "KSH/MBGuardBarActor.h"
#include "../../../../../../../Source/Runtime/UMG/Public/Components/WidgetComponent.h"
#include "../../../../../../../Source/Runtime/UMG/Public/Blueprint/UserWidget.h"

// Sets default values
AMBGuardBarActor::AMBGuardBarActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MBGuardBarUI = CreateDefaultSubobject<UWidgetComponent>("MBGuardBarUI");
	MBGuardBarUI->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMBGuardBarActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMBGuardBarActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMBGuardBarActor::UpdateLocation(FVector Location, FRotator Rotator)
{
	this->SetActorLocationAndRotation(Location, Rotator);
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "KSH/UI/MBSkillNameActor.h"
#include "../../../../../../../Source/Runtime/UMG/Public/Components/WidgetComponent.h"
#include "../../../../../../../Source/Runtime/UMG/Public/Blueprint/UserWidget.h"
// Sets default values
AMBSkillNameActor::AMBSkillNameActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MBSkillNameUI = CreateDefaultSubobject<UWidgetComponent>("MBSkillNameUI");
	MBSkillNameUI->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMBSkillNameActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMBSkillNameActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMBSkillNameActor::UpdateLocation(FVector Location, FRotator Rotator)
{
	this->SetActorLocationAndRotation(Location, Rotator);
}

void AMBSkillNameActor::UpdateScale(float mulTimes)
{
	MBSkillNameUI->SetRelativeScale3D(FVector(0.3f) * mulTimes);
}


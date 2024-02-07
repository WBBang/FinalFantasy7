// Fill out your copyright notice in the Description page of Project Settings.


#include "KSH/MBHpBarActor.h"

#include "../../../../../../../Source/Runtime/UMG/Public/Components/WidgetComponent.h"
#include "../../../../../../../Source/Runtime/UMG/Public/Blueprint/UserWidget.h"
// Sets default values
AMBHpBarActor::AMBHpBarActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MBHpBarUI = CreateDefaultSubobject<UWidgetComponent>("MBHpBarUI");
	MBHpBarUI->SetupAttachment(RootComponent);

	//ConstructorHelpers::FClassFinder<UUserWidget> HpUI(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/KSH/Blueprints/WBP_PlayerHP.WBP_PlayerHP'_C"));
	/*if ( HpUI.Succeeded() )
	{
		MBHpBarUI->SetWidgetClass(HpUI.Class);
		MBHpBarUI->SetRelativeRotation(FRotator(0.0f, 0.0f, -180.f));
		MBHpBarUI->SetDrawSize(FVector2D(400.0f, 30.0f));
	}
	*/
}

// Called when the game starts or when spawned
void AMBHpBarActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMBHpBarActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMBHpBarActor::UpdateLocation(FVector Location, FRotator Rotator)
{
	///this->SetActorLocation(Location);
	this->SetActorLocationAndRotation(Location, Rotator);
}
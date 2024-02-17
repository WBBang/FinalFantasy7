// Fill out your copyright notice in the Description page of Project Settings.


#include "KSH/UI/MBDamageTextUI.h"
#include "Components/TextRenderComponent.h"
#include "Curves/CurveVector.h"
#include "Components/TimelineComponent.h"
#include "Kismet/KismetTextLibrary.h"

// Sets default values
AMBDamageTextUI::AMBDamageTextUI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	textRender = CreateDefaultSubobject <UTextRenderComponent>(TEXT("textRender"));
	textRender->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMBDamageTextUI::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMBDamageTextUI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMBDamageTextUI::SetDamageText(int32 AttackType, int32 Damage)
{
	if ( AttackType == 0 )
	{
		// 공격인 경우
		textRender->SetTextRenderColor(FColor::Red);
	}
	else if ( AttackType == 1 )
	{
		// 가드인 경우
		textRender->SetTextRenderColor(FColor::Blue);
	}

	FText DamageText = UKismetTextLibrary::Conv_IntToText(Damage);
	textRender->SetText(DamageText);
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "KEC/FBHPWidget.h"

#include "Components/ProgressBar.h"

void UFBHPWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UFBHPWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	float curPercent = HPBarMid->GetPercent();
	float targetPercent = HPBar->GetPercent();
	float lerpPercent = FMath::Lerp<float>( curPercent, targetPercent, InDeltaTime * 20);

	HPBarMid->SetPercent(lerpPercent);
}

void UFBHPWidget::SetHP(int32 hp, int32 maxHP)
{
	HPBar->SetPercent((float)hp / maxHP);
}

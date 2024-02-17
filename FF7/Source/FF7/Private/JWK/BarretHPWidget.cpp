// Fill out your copyright notice in the Description page of Project Settings.


#include "JWK/BarretHPWidget.h"
#include "../../../../../../../Source/Runtime/UMG/Public/Components/TextBlock.h"
#include "../../../../../../../Source/Runtime/UMG/Public/Components/ProgressBar.h"


void UBarretHPWidget::SetBarrettHP(int32 BarrettHP, int32 BarrettMaxHP)
{

	BarrettCurHP->SetText(FText::AsNumber(BarrettHP));

	BarrettFullHP->SetText(FText::AsNumber(BarrettMaxHP));

	BarrettHPBar->SetPercent((float)BarrettHP / BarrettMaxHP);
}

void UBarretHPWidget::SetBarretSkillTime(int32 BarrettSkill, int32 BarrettMaxSkill)
{
	BarrettSkillBar->SetPercent((float)BarrettSkill / BarrettMaxSkill);
}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BarretHPWidget.generated.h"

/**
 *
 */
UCLASS()
class FF7_API UBarretHPWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, meta = ( BindWidget ))
	class UProgressBar* BarrettHPBar;

	UPROPERTY(EditAnywhere, meta = ( BindWidget ));
	class UTextBlock* BarrettCurHP;
	UPROPERTY(EditAnywhere, meta = ( BindWidget ));
	class UTextBlock* BarrettFullHP;

	void SetBarrettHP(int32 BarrettHP, int32 BarrettMaxHP);

};

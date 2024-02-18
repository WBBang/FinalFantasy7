// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BarrettGameOverWidget.generated.h"

/**
 *
 */
UCLASS()
class FF7_API UBarrettGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	UPROPERTY(EditAnywhere, meta = ( BindWidget ))
	class UButton* ButtonRestart;
	UPROPERTY(EditAnywhere, meta = ( BindWidget ))
	class UButton* ButtonQuit;

	UFUNCTION()
	void OnMyRestart();

	UFUNCTION()
	void OnMyQuit();
};

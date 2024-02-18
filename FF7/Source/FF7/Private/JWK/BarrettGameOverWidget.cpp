// Fill out your copyright notice in the Description page of Project Settings.


#include "JWK/BarrettGameOverWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UBarrettGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//버튼을 누르면 동작하게 함수를 연결하고싶다.
	ButtonRestart->OnClicked.AddDynamic(this, &UBarrettGameOverWidget::OnMyRestart);
	ButtonQuit->OnClicked.AddDynamic(this, &UBarrettGameOverWidget::OnMyQuit);
}

void UBarrettGameOverWidget::OnMyRestart()
{
	//현재 맵의 이름을 알고싶다.
	FString mapName = UGameplayStatics::GetCurrentLevelName(( GetWorld() ));
	//그 맵으로 다시 레벨을 재시작싶다.
	UGameplayStatics::OpenLevel(GetWorld(), FName(*mapName));
}

void UBarrettGameOverWidget::OnMyQuit()
{
	auto controller = GetWorld()->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame(GetWorld(), controller, EQuitPreference::Quit, false);
}
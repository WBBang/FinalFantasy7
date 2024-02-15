// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MBNameActor.generated.h"

UCLASS()
class FF7_API AMBNameActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMBNameActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* MBNameUI;

	UFUNCTION()
	void UpdateLocation(FVector Location, FRotator Rotator);

	UFUNCTION()
	void UpdateScale(float mulTimes);
};

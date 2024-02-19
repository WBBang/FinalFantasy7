// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MBFloor.generated.h"

UCLASS()
class FF7_API AMBFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMBFloor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// --------------- 게임 클리어 -----------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf <class ABrokenFloor> brokenFloor;

	UFUNCTION(BlueprintCallable)
	void MiddleBossGameClear();

};

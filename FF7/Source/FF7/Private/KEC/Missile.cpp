// Fill out your copyright notice in the Description page of Project Settings.


#include "KEC/Missile.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/CapsuleComponent.h"


// Sets default values
AMissile::AMissile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
}

// Called when the game starts or when spawned
void AMissile::BeginPlay()
{
	Super::BeginPlay();
	LaunchMissile();
}

// Called every frame
void AMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AMissile::LaunchMissile()
{
	// �̻��� UpVector Impulse
	FVector impulseDir = GetActorLocation().UpVector * impuslePos;
	meshComp->AddImpulse(impulseDir);


	UE_LOG(LogTemp, Log, TEXT("Hi"));
	FTimerHandle MyTimer;
	float Time = delayTime;
	GetWorld()->GetTimerManager().SetTimer(MyTimer, FTimerDelegate::CreateLambda([&]()
		{
		//�÷��̾� ���� ��������
			playerPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
			playerRotate = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorRotation();

		//�÷��̾� �������� �Ӹ� ������


			SetActorRotation(playerRotate);

		//�÷��̾� �������� �̵��ϱ�
			FVector p0 = GetActorLocation();
			FVector dir = playerPosition - p0;
			dir.Normalize();
			targetDir = dir * missileSpeed * GetWorld()->GetDeltaSeconds();
			SetActorLocation(p0 + targetDir);
			UE_LOG(LogTemp, Log, TEXT("Bye"));
			// TimerHandle �ʱ�ȭ
			GetWorld()->GetTimerManager().ClearTimer(MyTimer);
			
		}), Time, false);
}



// Fill out your copyright notice in the Description page of Project Settings.


#include "KEC/Missile.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Engine/SkeletalMesh.h"

// Sets default values
AMissile::AMissile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	capsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("capsuleComp"));
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));


	SetRootComponent(capsuleComp);
	meshComp->SetupAttachment(RootComponent);


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
	// �̻����� UpVector�� ���� ��� �ֱ�
	FVector impulseDir = meshComp->GetUpVector() * impuslePos;
	meshComp->AddImpulse(impulseDir);

	//������ 2��
	Delay(delayTime);
	CruiseMissile();
}



void AMissile::CruiseMissile()
{
	//�÷��̾� ��������
	FVector playerPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	//�÷��̾� �������� �̵��ϱ�
	FVector p0 = GetActorLocation();
	FVector dir = playerPosition - p0;
	dir.Normalize();
	SetActorLocation(dir * missileSpeed * GetWorld()->GetDeltaSeconds());
}

//������ �Լ�
void AMissile::Delay(float value)
{
	FTimerHandle timerHandle;
	GetWorld()->GetTimerManager().SetTimer(timerHandle, 
		FTimerDelegate::CreateLambda([&]()
			{
				GetWorld()->GetTimerManager().ClearTimer(timerHandle);
			}), value, false);
}


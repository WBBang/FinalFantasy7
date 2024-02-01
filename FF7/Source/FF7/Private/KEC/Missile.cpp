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

	missile = Cast<AMissile>(GetOwner());
	


}

// Called when the game starts or when spawned
void AMissile::BeginPlay()
{
	Super::BeginPlay();
	LaunchMissile();
	
	
	
	//������ 2��
	
}

// Called every frame
void AMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isLaunched) 
	{
		Delay();
	}
	missile->AddMovement
}

void AMissile::LaunchMissile()
{
	// �̻��� UpVector Impulse
	FVector impulseDir = meshComp->GetUpVector() * impuslePos;
	meshComp->AddImpulse(impulseDir);
	isLaunched = true;
}



void AMissile::CruiseMissile()
{
	meshComp->SetEnableGravity(false);
	meshComp->SetSimulatePhysics(false);
	SetActorLocation(meshComp->GetComponentLocation());
	//�÷��̾� ��������
	playerPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	
	//�÷��̾� �������� �̵��ϱ�
	FVector p0 = GetActorLocation();
	FVector dir = playerPosition - p0;
	dir.Normalize();
	targetPosition = dir * missileSpeed * GetWorld()->GetDeltaSeconds();
}

void AMissile::Delay()
{
	UE_LOG(LogTemp, Log, TEXT("Hi"));
	FTimerHandle MyTimer;
	float Time = delayTime;
	GetWorld()->GetTimerManager().SetTimer(MyTimer, FTimerDelegate::CreateLambda([&]()
		{
			// ������ ����
			CruiseMissile();
			UE_LOG(LogTemp, Log, TEXT("Bye"));
			// TimerHandle �ʱ�ȭ
			GetWorld()->GetTimerManager().ClearTimer(MyTimer);
			
		}), Time, false);
}



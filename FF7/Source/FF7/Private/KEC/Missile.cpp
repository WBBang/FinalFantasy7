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
	
	
	
	//딜레이 2초
	
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
	// 미사일 UpVector Impulse
	FVector impulseDir = meshComp->GetUpVector() * impuslePos;
	meshComp->AddImpulse(impulseDir);
	isLaunched = true;
}



void AMissile::CruiseMissile()
{
	meshComp->SetEnableGravity(false);
	meshComp->SetSimulatePhysics(false);
	SetActorLocation(meshComp->GetComponentLocation());
	//플레이어 가져오기
	playerPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	
	//플레이어 방향으로 이동하기
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
			// 실행할 내용
			CruiseMissile();
			UE_LOG(LogTemp, Log, TEXT("Bye"));
			// TimerHandle 초기화
			GetWorld()->GetTimerManager().ClearTimer(MyTimer);
			
		}), Time, false);
}



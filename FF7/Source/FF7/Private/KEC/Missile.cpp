// Fill out your copyright notice in the Description page of Project Settings.


#include "KEC/Missile.h"

#include "MovieSceneSequenceID.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMissile::AMissile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("sphereComp"));
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));

	SetRootComponent(sphereComp);
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetRelativeScale3D(FVector(3.0));

	sphereComp->SetSimulatePhysics(true);
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
	CruiseMissile();
}

void AMissile::LaunchMissile()
{
	// 미사일 UpVector Impulse
	//CapsuleComponent* comp = capsuleComponent;
	USphereComponent* sphere = sphereComp;
	FVector impulseDir = GetActorUpVector() * sphere->GetUpVector() * sphere->GetMass() * impuslePos;
	sphere->AddImpulse(impulseDir);
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, TEXT("Hello")); // 게임 화면
	dirSet = true;
}

void AMissile::CruiseMissile()
{

	FTimerHandle MyTimer;
	GetWorld()->GetTimerManager().SetTimer(MyTimer, FTimerDelegate::CreateLambda([&]()
	{
		//플레이어 방향가져오기
		FVector targetPos = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - GetActorLocation();
		targetPos.Normalize();
		//플레이어 방향으로 이동하기
		sphereComp->AddImpulse(targetPos * sphereComp->GetMass() * 3000);
		
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, TEXT("Bye")); // 게임 화면
		// TimerHandle 초기화
		GetWorld()->GetTimerManager().ClearTimer(MyTimer);
	}), delayTime, false);
}

void AMissile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionParticle, GetActorLocation(),GetActorRotation(), FVector(10));
	this->Destroy();
	
}

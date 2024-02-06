// Fill out your copyright notice in the Description page of Project Settings.


#include "KEC/Missile.h"

#include "MovieSceneSequenceID.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "NiagaraComponent.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMissile::AMissile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	capsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("capsuleComp"));
	SetRootComponent(capsuleComponent);
	capsuleComponent->SetSimulatePhysics(true);

	skeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("skeletalMeshComp"));
	skeletalMeshComp->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> skeletalMesh(TEXT(
		"/Script/Engine.SkeletalMesh'/Game/KEC/Asset/VigilanteContent/Projectiles/West_Missile_AGM114/SK_West_Missile_AGM114.SK_West_Missile_AGM114'"));
	if (skeletalMesh.Succeeded())
	{
		skeletalMeshComp->SetSkeletalMesh(skeletalMesh.Object);
	}

	MissileNiagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("MissileNiagara"));
	MissileNiagara->SetupAttachment(skeletalMeshComp);
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
	// �̻��� UpVector Impulse
	UCapsuleComponent* comp = capsuleComponent;
	FVector impulseDir = GetActorUpVector() * comp->GetUpVector() * comp->GetMass() * impuslePos;
	comp->AddImpulse(impulseDir);
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, TEXT("Hello")); // ���� ȭ��
	isRotating = true;
}

void AMissile::CruiseMissile()
{
	//�÷��̾� �������� ȸ��
	if (isRotating)
	{
		//FVector targetPos = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - GetActorLocation();
		//FRotator lookAtRotation = FRotator(0.0f, targetPos.Rotation().Yaw, targetPos.Rotation().Roll);
	}

	FTimerHandle MyTimer;
	GetWorld()->GetTimerManager().SetTimer(MyTimer, FTimerDelegate::CreateLambda([&]()
	{
		isRotating = false;
		capsuleComponent->SetSimulatePhysics(false);

		//�÷��̾� �������� �̵��ϱ�
		//targetDir = GetActorForwardVector() * missileSpeed * GetWorld()->GetDeltaSeconds();
		//SetActorLocation(GetActorLocation() + targetDir);
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, TEXT("Bye")); // ���� ȭ��
		// TimerHandle �ʱ�ȭ
		GetWorld()->GetTimerManager().ClearTimer(MyTimer);
	}), delayTime, false);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "KEC/FinalBossCharacter.h"
#include "Components/ArrowComponent.h"
#include "KEC/BossBullet.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFinalBossCharacter::AFinalBossCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//개틀링 발사 위치
	leftArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("leftArrowComp"));
	rightArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("rightArrowComp"));

	leftArrowComp->SetupAttachment(RootComponent);
	rightArrowComp->SetupAttachment(RootComponent);
	


	//보스캐릭터 SkeletalMesh
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT(
		"/Script/Engine.SkeletalMesh'/Game/KEC/Asset/SpiderMech/Mesh/SpiderMech/SK_SpriderMech.SK_SpriderMech'"));
	if (tempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	}
}

// Called when the game starts or when spawned
void AFinalBossCharacter::BeginPlay()
{
	Super::BeginPlay();
	Fire();
}

// Called every frame
void AFinalBossCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void AFinalBossCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AFinalBossCharacter::Fire()
{
	FTransform leftGun = leftArrowComp->GetComponentTransform();
	FTransform rightGun = rightArrowComp->GetComponentTransform();
	
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), fireVFX, leftGun);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), fireVFX, rightGun);

		
		
	UE_LOG(LogTemp, Warning, TEXT("fuck"));
	GetWorld()->SpawnActor<ABossBullet>(bulletFactory, leftGun);
	GetWorld()->SpawnActor<ABossBullet>(bulletFactory, rightGun);
	
}
		
		


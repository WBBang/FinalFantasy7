// Fill out your copyright notice in the Description page of Project Settings.


#include "KEC/FinalBossCharacter.h"
#include "Components/ArrowComponent.h"
#include "KEC/BossBullet.h"
#include "KEC/Missile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFinalBossCharacter::AFinalBossCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//개틀링 발사 위치
	leftArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("leftArrowComp"));
	rightArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("rightArrowComp"));

	//미사일 발사 위치
	missieLaunchArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("launchMissileArrowComp"));

	leftArrowComp->SetupAttachment(RootComponent);
	rightArrowComp->SetupAttachment(RootComponent);
	missieLaunchArrowComp->SetupAttachment(RootComponent);


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
	
	//Fire();
	//LauchMissile();
}

// Called every frame
void AFinalBossCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AttackLength();
	if(isDetected)
	{
		JumpAttack();
	}
	
	
		
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
	
	GetWorld()->SpawnActor<ABossBullet>(bulletFactory, leftGun);
	GetWorld()->SpawnActor<ABossBullet>(bulletFactory, rightGun);
}

void AFinalBossCharacter::LauchMissile()
{
	FTransform launchPos = missieLaunchArrowComp->GetComponentTransform();
	GetWorld()->SpawnActor<AMissile>(missileFactory, launchPos);
}

void AFinalBossCharacter::JumpAttack()
{
	FVector player = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FVector target = player - GetActorLocation();
	target.Normalize();

	if(bIsJumpAttack)
	{
		SetActorLocation(GetActorLocation() + target * jumpSpeed * GetWorld()->DeltaTimeSeconds , false);
	}
	
		bIsJumpAttack = false;

		
}

void AFinalBossCharacter::AttackLength()
{
	playerLength = GetDistanceTo(GetWorld()->GetFirstPlayerController()->GetPawn());
	if(playerLength < 1000)
	{
		isDetected = true;
	}
}

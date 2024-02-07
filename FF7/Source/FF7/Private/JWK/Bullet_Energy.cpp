// Fill out your copyright notice in the Description page of Project Settings.


#include "JWK/Bullet_Energy.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "KSH/MiddleBossCharacter.h"

// Sets default values
ABullet_Energy::ABullet_Energy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("sphereComp"));
	SetRootComponent(sphereComp);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	meshComp->SetupAttachment(RootComponent);

	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("movementComp"));

	// 총알 이동속도, bounce Set
	movementComp->InitialSpeed = 500.f;
	movementComp->MaxSpeed = 500.0f;
	movementComp->bShouldBounce = false;

	// 총알의 Collision Set
	sphereComp->SetGenerateOverlapEvents(true);
	sphereComp->SetCollisionProfileName(TEXT("PlayerAttack"));
	//meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);


	// 총알 크기 Set
	meshComp->SetWorldScale3D(FVector(0.2f));
	sphereComp->SetSphereRadius(1);
}

// Called when the game starts or when spawned
void ABullet_Energy::BeginPlay()
{
	Super::BeginPlay();
	movementComp->SetUpdatedComponent(sphereComp);

	FTimerHandle timerHandle;
	GetWorld()->GetTimerManager().SetTimer(timerHandle, FTimerDelegate::CreateLambda([this]()->void {this->Destroy(); }), 2, false);
}

// Called every frame
void ABullet_Energy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABullet_Energy::OnMyCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMiddleBossCharacter* middleBoss = Cast<AMiddleBossCharacter>(OtherActor);
	if ( nullptr != middleBoss )
	{
		middleBoss->MiddleBossDamagedBySkillBullet(3);
	}
}



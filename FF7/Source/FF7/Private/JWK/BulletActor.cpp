// Fill out your copyright notice in the Description page of Project Settings.


#include "JWK/BulletActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "KEC/FinalBossCharacter.h"
#include "KSH/MiddleBossCharacter.h"


ABulletActor::ABulletActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("sphereComp"));
	SetRootComponent(sphereComp);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	meshComp->SetupAttachment(RootComponent);

	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("movementComp"));

	// 총알 이동속도, bounce Set
	movementComp->InitialSpeed = 40000.f;
	movementComp->MaxSpeed = 40000.f;
	movementComp->bShouldBounce = false;

	// 총알의 Collision Set
	sphereComp->SetGenerateOverlapEvents(true);
	sphereComp->SetCollisionProfileName(TEXT("PlayerAttack"));
	//meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);


	// 총알 크기 Set
	meshComp->SetWorldScale3D(FVector(0.025f));
	sphereComp->SetSphereRadius(1.25);


}


void ABulletActor::BeginPlay()
{
	Super::BeginPlay();
	movementComp->SetUpdatedComponent(sphereComp);

	FTimerHandle timerHandle;
	GetWorld()->GetTimerManager().SetTimer(timerHandle, FTimerDelegate::CreateLambda([this]()->void {this->Destroy(); }), 1, false);
}

// Called every frame
void ABulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
/*
void ABulletActor::OnMyCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMiddleBossCharacter* middleBoss = Cast<AMiddleBossCharacter>(OtherActor);
	if ( nullptr != middleBoss )
	{
		UE_LOG(LogTemp, Log, TEXT("Damaged"));
		middleBoss->MiddleBossDamagedByBasicBullet(3);
	}
}
*/

void ABulletActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	AMiddleBossCharacter* middleBoss = Cast<AMiddleBossCharacter>(OtherActor);
	AFinalBossCharacter* finalBoss = Cast<AFinalBossCharacter>(OtherActor);
	if ( nullptr != middleBoss )
	{
		int randDamage = FMath::RandRange(1, 3);
		middleBoss->MiddleBossDamagedByBasicBullet(randDamage);

		// 총알은 사라지기
		Destroy();
	}

	if( nullptr != finalBoss)
	{
		finalBoss->TakeDamage(300);
		Destroy();
	}
}


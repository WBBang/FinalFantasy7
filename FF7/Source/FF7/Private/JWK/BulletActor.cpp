// Fill out your copyright notice in the Description page of Project Settings.


#include "JWK/BulletActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABulletActor::ABulletActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("sphereComp"));
	SetRootComponent(sphereComp);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	meshComp->SetupAttachment(RootComponent);

	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("movementComp"));

	// ÃÑ¾Ë ÀÌµ¿¼Óµµ, bounce Set
	movementComp->InitialSpeed = 6000.f;
	movementComp->MaxSpeed = 6000.f;
	movementComp->bShouldBounce = false;

	// ÃÑ¾ËÀÇ Collision Set
	sphereComp->SetCollisionProfileName(TEXT("Blockall"));
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);


	// ÃÑ¾Ë Å©±â Set
	meshComp->SetWorldScale3D(FVector(0.025f));
	sphereComp->SetSphereRadius(1.25);


}

// Called when the game starts or when spawned
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


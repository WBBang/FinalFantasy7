// Fill out your copyright notice in the Description page of Project Settings.


#include "JWK/Barrett.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/SkeletalMesh.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Engine/SkeletalMesh.h"

// Sets default values
ABarrett::ABarrett()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArmComp"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->SetWorldLocation(FVector(0, 70, 90));
	springArmComp->bUsePawnControlRotation = true;

	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("cameraComp"));
	cameraComp->SetupAttachment(springArmComp);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/JWK/ParagonMurdock/Characters/Heroes/Murdock/Meshes/Murdock.Murdock'"));
	if (tempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	}
}

// Called when the game starts or when spawned
void ABarrett::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABarrett::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}

// Called to bind functionality to input
void ABarrett::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("Forward / Backward"), this, &ABarrett::OnAxisVertical);

	PlayerInputComponent->BindAxis(TEXT("Right / Left"), this, &ABarrett::OnAxisHorizontal);

	PlayerInputComponent->BindAxis(TEXT("Turn Right / Left Mouse"), this, &ABarrett::OnAxisTurnYaw);

	PlayerInputComponent->BindAxis(TEXT("Look Up / Down Mouse"), this, &ABarrett::OnAxisLookupPitch);

	PlayerInputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &ABarrett::StartAttack);

}

void ABarrett::Move()
{
	FTransform trans = GetActorTransform();
	AddMovementInput(trans.TransformVector(direction));
}

void ABarrett::OnAxisVertical(float value)
{
	direction.X = value;
}

void ABarrett::OnAxisHorizontal(float value)
{
	direction.Y = value;
}

void ABarrett::OnAxisTurnYaw(float value)
{
	AddControllerYawInput(value);
}

void ABarrett::OnAxisLookupPitch(float value)
{
	AddControllerPitchInput(value);
}

void ABarrett::StartAttack()
{
	// 공격 애니메이션
}

void ABarrett::LineTrace()
{
	//적에게 대미지 적용
}


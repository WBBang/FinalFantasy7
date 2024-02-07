// Fill out your copyright notice in the Description page of Project Settings.


#include "JWK/Barrett.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/SkeletalMesh.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "JWK/BulletActor.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "JWK/Bullet_Energy.h"

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

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/JWK/Barrett_Mixamo/Barrett.Barrett'"));
	if (tempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		GetMesh()->SetWorldScale3D(FVector(0.1f));
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	}

	RifleMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RifleMeshComp"));
	RifleMeshComp->SetupAttachment(GetMesh(), TEXT("Rifle"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempRifleMesh(TEXT("/Script/Engine.StaticMesh'/Game/JWK/Rifle/Rifle.Rifle'"));
	// RifleMeshComp �˻��� �����ϸ�
	if (tempRifleMesh.Succeeded())
	{
		RifleMeshComp->SetStaticMesh(tempRifleMesh.Object);
		RifleMeshComp->SetRelativeLocationAndRotation(FVector(17.136384f, -319.395057f, 52.838305f), FRotator(-90,-180,2.422084f));
		RifleMeshComp->SetWorldScale3D(FVector(20, 35, 20));
	}
}

// Called when the game starts or when spawned
void ABarrett::BeginPlay()
{
	Super::BeginPlay();
	IsTargetLocked = false;
	CurFireTime = MaxFireTime;
	if (IsSkill)
	{
		EnergyFire();
		IsSkill = false;
	}
}

// Called every frame
void ABarrett::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();

	if (IsFire)
	{
		CurFireTime += DeltaTime;
		if (CurFireTime >= MaxFireTime)
		{
			Fire();
			CurFireTime = 0;
		}
	}
	

	if (HitActor)
	{
		/*APawn::GetController()->AController::SetControlRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),HitActor->GetActorLocation()));*/

		if (APawn::GetController())
		{
			// HitActor�� ��ȿ���� üũ
			if (HitActor->IsValidLowLevel())
			{
				// ���� ĳ������ ��ġ���� HitActor ���� ���ϴ� ȸ���� ���
				FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), HitActor->GetActorLocation());

				// �ε巯�� ���� ������ ���� ���� ��� (Lerp)
				FRotator LerpedRotation = FMath::Lerp(APawn::GetController()->GetControlRotation(), TargetRotation, DeltaTime * 5);

				// ĳ������ ��Ʈ�ѷ��� ȸ���� ����
				APawn::GetController()->AController::SetControlRotation(LerpedRotation);
			}
		}
	}

}

// �÷��̾� Ű �Է�
void ABarrett::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("Forward / Backward"), this, &ABarrett::OnAxisVertical);

	PlayerInputComponent->BindAxis(TEXT("Right / Left"), this, &ABarrett::OnAxisHorizontal);

	PlayerInputComponent->BindAxis(TEXT("Turn Right / Left Mouse"), this, &ABarrett::OnAxisTurnYaw);

	PlayerInputComponent->BindAxis(TEXT("Look Up / Down Mouse"), this, &ABarrett::OnAxisLookupPitch);

	PlayerInputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &ABarrett::StartAttack);

	PlayerInputComponent->BindAction(TEXT("Attack"), IE_Released, this, &ABarrett::EndAttack);

	PlayerInputComponent->BindAction(TEXT("LockOn"), IE_Pressed, this, &ABarrett::LockOn);

	PlayerInputComponent->BindAction(TEXT("Skill"), IE_Pressed, this, &ABarrett::EnergyFire);

	PlayerInputComponent->BindAction(TEXT("Roll"), IE_Pressed, this, &ABarrett::OnActionRoll);
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
	IsFire = true;
}

void ABarrett::EndAttack()
{
	IsFire = false;
	CurFireTime = MaxFireTime;
}

void ABarrett::Fire()
{
	
	// �Ѿ� ����
	FTransform t = RifleMeshComp->GetSocketTransform(TEXT("FirePosition"));
	GetWorld()->SpawnActor<ABulletActor>(bulletFactory, t);

}

void ABarrett::EnergyFire()
{
	IsSkill = true;

	ABullet_Energy* BulletEnergySpeed = NewObject<ABullet_Energy>();
	FTimerHandle MyTimer;
	float Time =1.5f;

	double Seconds = FPlatformTime::Seconds();
	int64 curMilSec = static_cast<int64>(Seconds * 1000);
	if (curMilSec - milliseconds > 5000) // 5�� ��Ÿ��
	{
		milliseconds = curMilSec;
		GetWorld()->GetTimerManager().SetTimer(MyTimer, FTimerDelegate::CreateLambda([&]()
			{
				UE_LOG(LogTemp, Log, TEXT("bye"));
				// ������ ����
				FTransform t = RifleMeshComp->GetSocketTransform(TEXT("FirePosition"));
				GetWorld()->SpawnActor<ABullet_Energy>(energyFactory, t);
				// TimerHandle �ʱ�ȭ
				GetWorld()->GetTimerManager().ClearTimer(MyTimer);
			}), Time, false);
	}
}

void ABarrett::LineTrace()
{
	//������ ����� ����
}

void ABarrett::LockOn()
{
	UE_LOG(LogTemp, Log, TEXT("LockOn"));
	if (!IsTargetLocked)
	{
		UE_LOG(LogTemp, Log, TEXT("IsTargetLocked"));
		TArray<AActor*> ignoreActors;
		ignoreActors.Add(this);
		FHitResult OutHit;

		bool result = UKismetSystemLibrary::SphereTraceSingleForObjects
		(
			// UObject * WorldContextObject
			GetWorld(),
			// const FVector Start
			GetActorLocation(),
			// const FVector End
			GetActorLocation() * cameraComp->GetForwardVector() * 10,
			// float Radius
			5000.0f,
			// const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes
			LockOnArea,
			// bool bTraceComplex
			false,
			// const TArray<AActor*>& ActorsToIgnore
			ignoreActors,
			// EDrawDebugTrace::Type DrawDebugType, 
			EDrawDebugTrace::ForDuration,
			// FHitResult & OutHit
			OutHit,
			// bool bIgnoreSelf
			true
		);
		//OutHit.GetActor();

		if (result)
		{
			IsTargetLocked = true;
			UKismetSystemLibrary::PrintString(GetWorld(), FString(TEXT("TargetLocked")));
			bool InputObject = UKismetSystemLibrary::IsValid(OutHit.GetActor());
			if (InputObject)
			{
				HitActor = OutHit.GetActor();
			}
		}
		else
		{

		}
	}

	else
	{
		UE_LOG(LogTemp, Log, TEXT("LockOff"));
		// code
		IsTargetLocked = false;
		HitActor = nullptr;
	}
}

void ABarrett::OnActionRoll()
{
	double Seconds = FPlatformTime::Seconds();
	int64 curMilSec = static_cast<int64>(Seconds * 1000);

	// ���� ����ð��� ����ϰ��ִ� �ð��� ���̰� 800ms �� �ʰ��Ѵٸ� Montage �� ����ϰ�ʹ�.

	if (curMilSec - milliseconds > 800)
	{
		milliseconds = curMilSec;
		this->PlayAnimMontage(rollMontage);
	}
}


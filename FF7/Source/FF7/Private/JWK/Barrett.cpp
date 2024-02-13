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
#include "../../../../../../../Source/Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Camera/PlayerCameraManager.h"

///////////////////////// Barrett /////////////////////////
ABarrett::ABarrett()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArmComp"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->SetWorldLocation(FVector(0, 40, 120));
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
	// RifleMeshComp 검색이 성공하면
	if (tempRifleMesh.Succeeded())
	{
		RifleMeshComp->SetStaticMesh(tempRifleMesh.Object);
		RifleMeshComp->SetRelativeLocationAndRotation(FVector(17.136384f, -319.395057f, 52.838305f), FRotator(-90,-180,2.422084f));
		RifleMeshComp->SetWorldScale3D(FVector(20, 35, 20));
	}



	/////////////////////////// 애니메이션 /////////////////////////

	///* 기본공격 */
	//static ConstructorHelpers::FObjectFinder<UAnimMontage> BasicAttackRef(TEXT("/Script/Engine.AnimMontage'/Game/JWK/Animation/Montage/Attack/MT_BasicAttack.MT_BasicAttack'"));
	//if ( BasicAttackRef.Object )
	//{
	//	BasicAttackMontage = BasicAttackRef.Object;
	//}

	///* 우와앙 빵 */
	//static ConstructorHelpers::FObjectFinder<UAnimMontage> SkillAttackRef(TEXT("/Script/Engine.AnimMontage'/Game/JWK/Animation/Montage/Attack/MT_WangBBang.MT_WangBBang'"));
	//if ( SkillAttackRef.Object )
	//{
	//	SkillAttackMontage = SkillAttackRef.Object;
	//}
}

// Called when the game starts or when spawned
void ABarrett::BeginPlay()
{
	Super::BeginPlay();
	IsTargetLocked = false;
	CurFireTime = MaxFireTime;
	
}

// Called every frame
void ABarrett::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();

	if ( IsSkill )
	{
		EnergyFire();
		IsSkill = false;
	}

	if (IsFire)
	{
		CurFireTime += DeltaTime;                                                  // auto Fire 타이머
		AttackEndTime += DeltaTime;                                                // IsFire 타이머

		FTransform s = RifleMeshComp->GetSocketTransform(TEXT("FirePosition"));    // 소환 위치

		if ( CurFireTime >= MaxFireTime )
		{
			Fire();
			// 기본공격 파티클 생성
			UParticleSystemComponent* SpawnBasic = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), boom, s);

			CurFireTime = 0;

			// 기본공격 길이가 3초가 되면
			if ( AttackEndTime >= 3 )
			{
				this->PlayAnimMontage(BasicAttackMontage);

				// 기본공격끝 파티클 생성
				UParticleSystemComponent* SpawnBasicEnd = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), basicAttackEnd, s);

				// 기본공격 길이 초기화
				AttackEndTime = 0;
			}
		}
	}
	// 락온 타겟이 있다면
	if (HitActor)
	{
		/*APawn::GetController()->AController::SetControlRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),HitActor->GetActorLocation()));*/

		if (APawn::GetController())
		{
			// HitActor이 유효한지 체크
			if ( HitActor->IsValidLowLevel() )
			{
				// 현재 캐릭터의 위치에서 HitActor 쪽을 향하는 회전값 계산
				FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), HitActor->GetActorLocation());

				// 부드러운 에임 변경을 위해 보간 사용 (Lerp)
				FRotator LerpedRotation = FMath::Lerp(APawn::GetController()->GetControlRotation(), TargetRotation, DeltaTime * 5);

				// 캐릭터의 컨트롤러에 회전값 설정
				APawn::GetController()->AController::SetControlRotation(LerpedRotation);
			}
		}
	}

}

///////////////////////// 플레이어 키 입력 /////////////////////////
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


///////////////////////// 기본공격 /////////////////////////
void ABarrett::Fire()
{
	// 총알 생성
	FTransform t = RifleMeshComp->GetSocketTransform(TEXT("FirePosition"));

	GetWorld()->SpawnActor<ABulletActor>(bulletFactory, t);

	//double Seconds = FPlatformTime::Seconds();

	//int64 curMilSec = static_cast<int64>( Seconds * 1000 );

	//FTimerHandle BasicTimer;

	//float BasicTime = 2;                                                       // 딜레이 타임

	//
	//if ( curMilSec - milliseconds > 3000 )                                     // 3초 쿨타임
	//{
	//	milliseconds = curMilSec;
	//	GetWorld()->GetTimerManager().SetTimer(BasicTimer, FTimerDelegate::CreateLambda([ & ] ()
	//		{
	//			// 실행할 내용
	//			
	//			// TimerHandle 초기화
	//			GetWorld()->GetTimerManager().ClearTimer(BasicTimer);
	//		}), BasicTime, false);
	//}
}

///////////////////////// 기본공격 시작 끝 /////////////////////////
void ABarrett::StartAttack()
{
	if ( autofire )
	{
		IsFire = true;
	}
}

void ABarrett::EndAttack()
{
	IsFire = false;
	CurFireTime = MaxFireTime;
	StopAnimMontage();
}

void ABarrett::IsAutoAttack(bool isAttacking)
{
	autofire = isAttacking;
	IsFire = isAttacking;
	/*if ( IsFire )
	{
		this->PlayAnimMontage(BasicAttackMontage);
	}
	else
	{
		StopAnimMontage();
	}*/
}


///////////////////////// 스킬공격 /////////////////////////
void ABarrett::EnergyFire()
{
	
	double Seconds = FPlatformTime::Seconds();
	int64 curMilSec = static_cast<int64>( Seconds * 1000 );
	IsSkill = true;
	FTimerHandle SkillTimer;
	float SkillTime =2;                                                       // 딜레이 타임

	FTransform s = RifleMeshComp->GetSocketTransform(TEXT("FirePosition"));   // 소환 위치
	if ( curMilSec - milliseconds > 5000 )
	{
		// Sparkle Emitter 총구 위치에 Spawn
		UParticleSystemComponent* SpawnedEnergy = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), sparkle, s);

		milliseconds = curMilSec;

		// 스킬공격 몽타주 재생
		this->PlayAnimMontage(SkillAttackMontage);

		// 딜레이 2 초
		GetWorld()->GetTimerManager().SetTimer(SkillTimer, FTimerDelegate::CreateLambda([ & ] ()
			{
				// 실행할 내용

				FTransform t = RifleMeshComp->GetSocketTransform(TEXT("FirePosition"));
				GetWorld()->SpawnActor<ABullet_Energy>(energyFactory, t);
				if ( nullptr == WangBBang )
				{
					return;
				}
				GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(WangBBang, 1.0f);
				// TimerHandle 초기화
				GetWorld()->GetTimerManager().ClearTimer(SkillTimer);
			}), SkillTime, false);

	}
}


///////////////////////// 공격 당함 /////////////////////////
void ABarrett::BarrettDamaged(int32 damage)
{
	BarretHP -= damage;
	if ( BarretHP <= 0 )
	{
		BarretHP = 0;
	}
}

////////////////////////// 락온 ////////////////////////
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

		if (result)  // 만약 맞은 타겟이 있다면
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
			UKismetSystemLibrary::PrintString(GetWorld(), FString(TEXT("TargetUnLockced")));
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

//void ABarrett::PlayMontage(UAnimMontage* NewMontage)
//{
//	UAnimInstance* Animinstance = GetMesh()->GetAnimInstance();
//	Animinstance->StopAllMontages(0.0f);
//	Animinstance->Montage_Play(NewMontage);
//}

////////////////////////// 구르기 //////////////////////////
void ABarrett::OnActionRoll()
{
	double Seconds = FPlatformTime::Seconds();
	int64 curMilSec = static_cast<int64>(Seconds * 1000);

	// 만약 현재시간과 기억하고있던 시간의 차이가 800ms 를 초과한다면 Montage 를 재생하고싶다.

	if (curMilSec - milliseconds > 800)
	{
		milliseconds = curMilSec;
		this->PlayAnimMontage(rollMontage);
	}
}


// Fill out your copyright notice in the Description page of Project Settings.

#include "KSH/MiddleBossCharacter.h"
#include "KSH/MBAIController.h"
#include "KSH/MBAnimInstance.h"
#include "KSH/ShockWaveAOE.h"
#include "GuardSuccessAOE.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "KSH/MBHpBarActor.h"
#include "KSH/MBGuardBarActor.h"
#include "KEC/LevelTransitionPortal.h"
#include "Engine/SkeletalMesh.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "JWK/Barrett.h"
#include "KSH/UI/MBNameActor.h"
#include "KSH/UI/MBSkillNameActor.h"

// Sets default values
AMiddleBossCharacter::AMiddleBossCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AMBAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	// 캐릭터 mesh
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/KSH/ParagonSteel/Characters/Heroes/Steel/Meshes/Steel.Steel'"));
	if ( tempMesh.Succeeded() )
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		GetMesh()->SetWorldScale3D(FVector(0.8f));
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	}

	// 회전 자연스럽게 설정
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);

	// HP UI 뜰 위치
	dummyCubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("dummyCubeMesh"));
	dummyCubeMesh->SetupAttachment(RootComponent);
	dummyCubeMesh->SetRelativeLocation(FVector(10.0f, 0, 120.0f));
	dummyCubeMesh->SetRelativeScale3D(FVector(0.2f));
	dummyCubeMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	dummyCubeMesh->bHiddenInGame = true;

	// 기본 공격 Collision
	rightHandComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("rightHandComp"));
	rightHandComp->SetupAttachment(GetMesh(), TEXT("rhandSocket"));
	rightHandComp->SetRelativeLocation(FVector(-1.1f, 0.45f, 0));
	rightHandComp->SetRelativeRotation(FRotator(90, 0, -5));
	rightHandComp->SetCapsuleRadius(24);
	rightHandComp->SetGenerateOverlapEvents(true);
	rightHandComp->SetCollisionProfileName(TEXT("NoCollision"));
	//rightHandComp->SetCollisionProfileName(TEXT("EnemyAttack"));

	leftHandComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("leftHandComp"));
	leftHandComp->SetupAttachment(GetMesh(), TEXT("lhandSocket"));
	leftHandComp->SetRelativeLocation(FVector(2.2f, -1.89f, 0));
	leftHandComp->SetRelativeRotation(FRotator(90.0f, 194.0f, 186.0f));
	leftHandComp->SetCapsuleRadius(24);
	leftHandComp->SetGenerateOverlapEvents(true);
	leftHandComp->SetCollisionProfileName(TEXT("NoCollision"));
	//leftHandComp->SetCollisionProfileName(TEXT("EnemyAttack"));

	// 가드 시 생기는 쉴드
	ShieldComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShieldComp"));
	ShieldComp->SetRelativeScale3D(FVector(2.3));
	ShieldComp->SetupAttachment(RootComponent);
	ShieldComp->SetCollisionProfileName(TEXT("NoCollision"));
	ConstructorHelpers::FObjectFinder<UStaticMesh>sphereTemp(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	ConstructorHelpers::FObjectFinder<UMaterial>shieldMatTemp(TEXT("/Script/Engine.Material'/Game/KSH/VX/ShieldMaterial.ShieldMaterial'"));
	if ( sphereTemp.Succeeded() && shieldMatTemp.Succeeded())
	{
		ShieldComp->SetStaticMesh(sphereTemp.Object);
		ShieldComp->SetMaterial(0, shieldMatTemp.Object);
	}
	ShieldComp->SetVisibility(false);
}

// Called when the game starts or when spawned
void AMiddleBossCharacter::BeginPlay()
{
	Super::BeginPlay();
	MiddleBossHP = MiddleBossMaxHP;
	movementComp = GetCharacterMovement();

	IsAttacking = false;
	//IsGuarding = false;
	IsGuardDeco = false;
	GuardingDamage = 0;

	player = GetWorld()->GetFirstPlayerController()->GetPawn();
	FVector loc = dummyCubeMesh->GetComponentLocation();
	FVector locHP = FVector(loc.X, loc.Y, loc.Z + 20);
	FVector locGuard = FVector(loc.X, loc.Y, loc.Z + 5);
	FVector locName = FVector(loc.X, loc.Y, loc.Z + 40);
	FVector locSkillName = FVector(loc.X, loc.Y, loc.Z + 60);
	hpBarUI = GetWorld()->SpawnActor<AMBHpBarActor>(hpBar, locHP, FRotator(0, 0, 0));
	guardBarUI = GetWorld()->SpawnActor<AMBGuardBarActor>(guardBar, locGuard, FRotator(0, 0, 0));
	MBNameUI = GetWorld()->SpawnActor<AMBNameActor>(MBName, locName, FRotator(0, 0, 0));
	MBSkillNameUI = GetWorld()->SpawnActor<AMBSkillNameActor>(MBSkillName, locSkillName, FRotator(0, 0, 0));

	guardBarUI->SetActorHiddenInGame(true);
	MBSkillNameUI->SetActorHiddenInGame(true);
}

// Called every frame
void AMiddleBossCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 테스트용 디버그 구 생성
	// AttackRange이하면 공격 가능
	//DrawDebugSphere(GetWorld(), GetActorLocation(), GetAIAttackRange(), 16, FColor::Blue, false, 0.1f);

	// SkillRange 이상이면 기열파나 뛰어오기
	//DrawDebugSphere(GetWorld(), GetActorLocation(), GetAISkillRange(), 16, FColor::Yellow, false, 0.1f);

	if ( nullptr != hpBarUI && nullptr != guardBarUI  && nullptr != MBNameUI && nullptr != MBSkillNameUI )
	{
		// 항상 HP UI 앞면이 보이고 보스 몬스터 머리위에 떠있게
		FVector loc = dummyCubeMesh->GetComponentLocation();
		FVector camLoc = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation();
		FVector locHP = FVector(loc.X, loc.Y, loc.Z + 20);

		// 항상 일정한 크기 유지
		float distance = ( ( loc - camLoc ).Length() ) * 0.001;
		if ( distance > 4 ) distance = 4.0f;
		else if ( distance < 1 ) distance = 1.0f;

		FRotator LookAtRotation = FRotationMatrix::MakeFromX(camLoc - dummyCubeMesh->GetComponentLocation()).Rotator();
		hpBarUI->UpdateLocation(locHP, LookAtRotation);

		hpBarUI->UpdateScale(distance);
		guardBarUI->UpdateScale(distance);
		MBNameUI->UpdateScale(distance);
		MBSkillNameUI->UpdateScale(distance);

		// 거리 비율에 따라 위치 수정
		FVector locGuard = FVector(loc.X, loc.Y, loc.Z + 5 - (distance * 5));
		guardBarUI->UpdateLocation(locGuard, LookAtRotation);

		float locNameZ = distance * 30;
		if ( locNameZ > 56 ) locNameZ = 56;
		else if ( locNameZ < 35 ) locNameZ = 35;
		FVector locName = FVector(loc.X, loc.Y + 10, loc.Z + locNameZ);
		MBNameUI->UpdateLocation(locName, LookAtRotation);

		float locSkillNameZ = locNameZ + 30;
		if ( locSkillNameZ > 85 ) locSkillNameZ = 85;
		else if ( locSkillNameZ < 60 ) locSkillNameZ = 60;
		FVector locSkillName = FVector(loc.X, loc.Y + 10, loc.Z + locSkillNameZ);
		MBSkillNameUI->UpdateLocation(locSkillName, LookAtRotation);
	}
}

// 델리게이트가 발생할 때까지 몽타주 재생 명령 내리지 못하게
void AMiddleBossCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	auto AnimInstance = Cast<UMBAnimInstance>(GetMesh()->GetAnimInstance());
	if ( nullptr == AnimInstance ) return;

	AnimInstance->OnMontageEnded.AddDynamic(this, &AMiddleBossCharacter::OnMontageEnded);
}

// Called to bind functionality to input
void AMiddleBossCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMiddleBossCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	ABarrett* barrett = Cast<ABarrett>(OtherActor);
	// 충돌대상이 플레이어라면
	if ( nullptr != barrett )
	{
		IsDuringAttack = true;
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, TEXT("Attack11"));
		UE_LOG(LogTemp, Log, TEXT("Attack"));

		// 플레이어 데미지 처리 함수 호출
		barrett->BarrettDamaged(5);
	}
}

void AMiddleBossCharacter::SetRightHandCompColl(bool IsColl)
{
	// 공격 중이라면
	if ( IsColl ) rightHandComp->SetCollisionProfileName(TEXT("EnemyAttack"));
	else rightHandComp->SetCollisionProfileName(TEXT("NoCollision"));
}

void AMiddleBossCharacter::SetLeftHandCompColl(bool IsColl)
{
	// 공격 중이라면
	if ( IsColl ) leftHandComp->SetCollisionProfileName(TEXT("EnemyAttack"));
	else leftHandComp->SetCollisionProfileName(TEXT("NoCollision"));
}

// 중간보스 게임 클리어
void AMiddleBossCharacter::MBGameClear()
{
	if ( IsDying ) return;
	if ( !IsDyingDeco ) return;

	IsDying = true;
	IsDyingDeco = false;

	auto AnimInstance = Cast<UMBAnimInstance>(GetMesh()->GetAnimInstance());
	if ( nullptr == AnimInstance ) return;

	AnimInstance->PlayDieMontage();

	// 막 보스로 넘어가는 문 소환
	FVector t = FVector(-130.0f, 670.0f, 80.0f);
	GetWorld()->SpawnActor<ALevelTransitionPortal>(MoveToFinalBossMapFactory, t, FRotator(0.0f));
}

// 기본 스킬로 맞은 경우
void AMiddleBossCharacter::MiddleBossDamagedByBasicBullet(int32 damage)
{
	// 보스한테 데미지 처리
	MiddleBossDamaged(damage);
}

// 우와아왕빵으로 맞은 경우
void AMiddleBossCharacter::MiddleBossDamagedBySkillBullet(int32 damage)
{
	// 가드 상태가 아니라면
	if ( false == IsGuardDeco )
	{
		// 경직 상태
		IsHitStuning = true;

		// 경직 애니메이션 호출


		// 경직 애니메이션 끝날 때 IsHitStuning = false 처리 하기
	}

	// 보스한테 데미지 처리
	MiddleBossDamaged(damage);
}

// 플레이어에게 공격 당한 경우 (어떤 공격이든 항상 호출)
void AMiddleBossCharacter::MiddleBossDamaged(int32 damage)
{
	// 가드 중이라면
	if ( true == IsGuardDeco )
	{
		// 피 줄어드는 대신 가드에 데미지 누적
		GuardingDamage += damage;

		// 가드 데미지가 카운터 가능 데미지(CounterDamage)까지 도달했고
		// 기열파 애니메이션이 실행중이 아니라면
		if ( !IsGuardSuccessDeco && GuardingDamage >= CounterDamage )
		{
			//UE_LOG(LogTemp, Log, TEXT("IsGuardSuccessing"));
			IsGuardSuccessDeco = true;
		}
	}

	// 가드 중이 아니라면
	else
	{
		//UE_LOG(LogTemp, Log, TEXT("Damaged"));
		// 데미지 받고
		MiddleBossHP -= damage;

		// 0이하라면
		if ( MiddleBossHP <= 0 )
		{
			MiddleBossHP = 0;

			// 중간보스 클리어 처리
			IsDyingDeco = true;
		}

		// 30% 확률로 
		int randomNum = FMath::RandRange(0, 9);
		//if (randomNum < 3) // 0, 1, 2
		{
			IsGuardDeco = true;
		}
	}
}

void AMiddleBossCharacter::SetIsGuarding(bool isGuarding)
{
	IsGuardDeco = isGuarding;
}

// 애니메이션 끝
void AMiddleBossCharacter::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	// 평타 몽타주였다면
	if ( Montage->GetFName() == "M_AttackMontage" )
	{
		UE_LOG(LogTemp, Log, TEXT("Attack Montage End"));
		IsAttacking = false;
	}

	// 가드 몽타주였다면
	else if ( Montage->GetFName() == "M_Guard_Montage" )
	{
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, TEXT("Guard End"));
		//UE_LOG(LogTemp, Log, TEXT("Guard Montage End"));

		// 가드 관련 변수 초기화
		GuardingDamage = 0;
		IsGuarding = false;
		IsGuardDeco = false;
		guardBarUI->SetActorHiddenInGame(true);
		ShieldComp->SetVisibility(false);

		// 스킬 이름 UI 숨기기
		MBSkillNameUI->SetActorHiddenInGame(true);

		OnAttackFinished.ExecuteIfBound();
		return;
	}

	// 지면 충격파 몽타주였다면
	else if ( Montage->GetFName() == "M_ShockWaveMontage" )
	{
		IsShockWaving = false;

		// 스킬 이름 UI 숨기기
		MBSkillNameUI->SetActorHiddenInGame(true);

		OnShockWaveFinished.ExecuteIfBound();
		return;
	}

	// 기열파 몽타주였다면
	else if ( Montage->GetFName() == "M_GuardSuccessMontage" )
	{
		// 애니메이션 관련 변수 초기화
		IsGuardSuccessing = false;

		UE_LOG(LogTemp, Log, TEXT("GuardSuccess End"));

		// 가드 관련 변수 초기화
		GuardingDamage = 0;
		IsGuarding = false;
		IsGuardDeco = false;

		// 스킬 이름 UI 숨기기
		MBSkillNameUI->SetActorHiddenInGame(true);

		guardBarUI->SetActorHiddenInGame(true);

		IsGuardSuccessing = false;
		IsGuardSuccessDeco = false;

		OnAttackFinished.ExecuteIfBound();
		return;
	}

	else if ( Montage->GetFName() == "M_Die" )
	{
		IsDying = false;
		IsDyingDeco = false;
		return;
	}

	// BT에 끝난거 알려주기
	// 나중에 몽타주별로 나눠야 함 (우선은 귀찮으니 하나로..ㅎ)
	OnAttackFinished.ExecuteIfBound();
}

// 가드
void AMiddleBossCharacter::Guard()
{
	if ( IsGuarding ) return;
	if ( !IsGuardDeco ) return;
	MBSkillNameUI->SetActorHiddenInGame(false);
	SkillName = FString(TEXT("가드"));
	guardBarUI->SetActorHiddenInGame(false);
	GuardingDamage = 0;
	IsGuarding = true;
	IsGuardSuccessDeco = false;
	ShieldComp->SetVisibility(true);

	auto AnimInstance = Cast<UMBAnimInstance>(GetMesh()->GetAnimInstance());
	if ( nullptr == AnimInstance ) return;

	AnimInstance->PlayGuardMontage();
}

// 기본 공격
void AMiddleBossCharacter::Attack()
{
	if ( IsAttacking ) return;

	auto AnimInstance = Cast<UMBAnimInstance>(GetMesh()->GetAnimInstance());
	if ( nullptr == AnimInstance ) return;

	AnimInstance->PlayAttackMontage();
	IsAttacking = true;
}

// 가드 성공 - 기열파
void AMiddleBossCharacter::GuardSuccess()
{
	if ( IsGuardSuccessing ) return;
	if ( !IsGuardSuccessDeco ) return;

	MBSkillNameUI->SetActorHiddenInGame(false);
	SkillName = FString(TEXT("기열파"));

	auto AnimInstance = Cast<UMBAnimInstance>(GetMesh()->GetAnimInstance());
	if ( nullptr == AnimInstance ) return;

	AnimInstance->PlayGuardSuccessMontage();


	FTimerHandle MyTimer;
	float Time = 0.35f;
	GetWorld()->GetTimerManager().SetTimer(MyTimer, FTimerDelegate::CreateLambda([ & ] ()
		{
			//UE_LOG(LogTemp, Log, TEXT("bye"));
			// 카메라 흔들기
			if ( nullptr == CSShockWave )return;
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(CSShockWave, 1.0f);

			FRotator rot = FRotationMatrix::MakeFromX(player->GetActorLocation() - GetActorLocation()).Rotator();
			FVector loc = FVector(player->GetActorLocation().X, player->GetActorLocation().Y, player->GetActorLocation().Z - 90.0f);
			GetWorld()->SpawnActor<AGuardSuccessAOE>(aoeActor, loc, rot);

			// TimerHandle 초기화
			GetWorld()->GetTimerManager().ClearTimer(MyTimer);
		}), Time, false);

	IsGuardSuccessing = true;
	IsGuardSuccessDeco = false;
}

// 지면 충격파
void AMiddleBossCharacter::ShockWave()
{
	if ( IsShockWaving ) return;

	MBSkillNameUI->SetActorHiddenInGame(false);
	SkillName = FString(TEXT("지면 충격파"));

	auto AnimInstance = Cast<UMBAnimInstance>(GetMesh()->GetAnimInstance());
	if ( nullptr == AnimInstance ) return;

	AnimInstance->PlayShockWaveMontage();

	FTimerHandle MyTimer;
	float Time = 0.35f;
	GetWorld()->GetTimerManager().SetTimer(MyTimer, FTimerDelegate::CreateLambda([ & ] ()
		{
			//UE_LOG(LogTemp, Log, TEXT("bye"));
			// 카메라 흔들기
			if ( nullptr == CSShockWave )return;
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(CSShockWave, 1.0f);

			FVector loc = FVector(GetActorLocation().X, GetActorLocation().Y, 30.0f);
			FRotator rot = FRotationMatrix::MakeFromX(player->GetActorLocation() - GetActorLocation()).Rotator();
			GetWorld()->SpawnActor<AShockWaveAOE>(shockWaveActor, loc, rot);

			// TimerHandle 초기화
			GetWorld()->GetTimerManager().ClearTimer(MyTimer);
		}), Time, false);

	IsShockWaving = true;
}

// 랜덤 순찰 범위
float AMiddleBossCharacter::GetAIPatrolRadius()
{
	return 800.0f;
}

// 플레이어 인지 범위
float AMiddleBossCharacter::GetAIDetectRange()
{
	return 2000.0f;
}

// 플레이어 공격할 수 있는 범위
float AMiddleBossCharacter::GetAIAttackRange()
{
	canAttackRange = 300.0f;
	return canAttackRange;
}

// 플레이어에게 스킬쓸 수 있는 범위
float AMiddleBossCharacter::GetAISkillRange()
{
	canSkillRange = 1000.0f;
	return canSkillRange;
}

float AMiddleBossCharacter::GetAITurnSpeed()
{
	return 0.0f;
}

bool AMiddleBossCharacter::GetAIGuardingSuccess()
{
	return IsGuardSuccessDeco;
}

bool AMiddleBossCharacter::GetAIGuarding()
{
	return IsGuardDeco;
}

bool AMiddleBossCharacter::GetAIDying()
{
	return IsDyingDeco;
}

void AMiddleBossCharacter::SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished)
{
	OnAttackFinished = InOnAttackFinished;
}

void AMiddleBossCharacter::SetAIShockWaveDelegate(const FAICharacterShockWaveFinished& InOnShockWaveFinished)
{
	OnShockWaveFinished = InOnShockWaveFinished;
}

void AMiddleBossCharacter::AttackByAI()
{
	// 공격
	Attack();
}

void AMiddleBossCharacter::ShockWaveByAI()
{
	ShockWave();
}

void AMiddleBossCharacter::GuardByAI()
{
	Guard();
}

void AMiddleBossCharacter::GuardSuccessByAI()
{
	GuardSuccess();
}

void AMiddleBossCharacter::DieByAI()
{
	MBGameClear();
}

// 스피드 변환 함수
void AMiddleBossCharacter::SpeedChangeByAI(float Speed)
{
	movementComp->MaxWalkSpeed = Speed;
}


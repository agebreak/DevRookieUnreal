// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
#include "MyAnimInstance.h"
#include "MyWeapon.h"
#include "CharacterStatComponent.h"
#include "DrawDebugHelpers.h"
#include "ProjectDRU.h"
#include "EngineMinimal.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->TargetArmLength = 400.0f; 
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	Camera->SetupAttachment(SpringArm);

	AttackEndComboState();
	SetControlMode(EControlMode::DIABLO);

	ArmLengthSpeed = 3.0f;
	ArmRotationSpeed = 10.0f;
	//GetCharacterMovement()->JumpZVelocity = 800.0f;				// 캐릭터의 점프 범위를 설정할 수 있다. 기본값은 420

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("MyCharacter"));
	
	AttackRange = 200.0f;
	AttackRadius = 50.0f;

	MaxHpPoint = 500.0f;
	CurrentHpPoint = MaxHpPoint;

	//UE_LOG(LogProjectDRU, Warning, TEXT("GetMesh() : %s"), *GetMesh()->GetName());
	//if (GetMesh()->DoesSocketExist(TEXT("myWeapon_r")))		// 현재 4.22.2버전에서 DoesSocketExist 함수가 소켓을 찾지 못하고 false를 반환하는 버그 발생.. 추후 고쳐지면 사용하거나, 다른 방법 필요.
	{
		Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_WEAPON(TEXT("/Game/InfinityBladeWeapons/Weapons/Blade/Swords/Blade_BlackKnight/SK_Blade_BlackKnight.SK_Blade_BlackKnight"));

		if (SK_WEAPON.Succeeded())
		{
			Weapon->SetSkeletalMesh(SK_WEAPON.Object);
		}

		Weapon->SetupAttachment(GetMesh(), TEXT("myWeapon_r"));
	}
	ABLOG(Warning, TEXT("DoesExist : %s"), (GetMesh()->DoesSocketExist(TEXT("myWeapon_r"))) ? TEXT("true") : TEXT("false"));

	CharacterStat = CreateDefaultSubobject<UCharacterStatComponent>(TEXT("CHARACTERSTAT"));
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	auto CurWeapon = GetWorld()->SpawnActor<AMyWeapon>(FVector::ZeroVector, FRotator::ZeroRotator);
	if (nullptr != CurWeapon)
	{
		CurWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("myWeapon_r"));
	}
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, ArmLengthTo, DeltaTime, ArmLengthSpeed);

	switch (CurrentControlMode)
	{
	case EControlMode::DIABLO:
		SpringArm->RelativeRotation = FMath::RInterpTo(SpringArm->RelativeRotation, ArmRotationTo, DeltaTime, ArmRotationSpeed);

		if (DirectionToMove.SizeSquared() > 0.0f)
		{
			GetController()->SetControlRotation(FRotationMatrix::MakeFromX(DirectionToMove).Rotator());
			AddMovementInput(DirectionToMove);
		}
		break;
	}
}

void AMyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AnimInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
	ABCHECK(AnimInstance != nullptr);

	AnimInstance->OnMontageEnded.AddDynamic(this, &AMyCharacter::OnAttackMontageEnded);
	AnimInstance->OnNextAttackCheck.AddLambda([this]() {
		CanNextCombo = false;
		if (IsComboInputOn)
		{
			AttackStartComboState();
			AnimInstance->JumpToAttackMontageSection(CurrentCombo);
		}
	});

	AnimInstance->OnAttackHitCheck.AddUObject(this, &AMyCharacter::AttackCheck);

	CharacterStat->OnHPIsZero.AddLambda([this]() -> void {
		ABLOG(Warning, TEXT("OnHPIsZero"));
		AnimInstance->SetDeadAnim();
		SetActorEnableCollision(false);
	});
}

void AMyCharacter::PossessedBy(AController * NewController)
{
	Super::PossessedBy(NewController);
	ABLOG(Warning, TEXT("AMyCharacter PossessedBy"));
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AMyCharacter::Attack);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMyCharacter::MoveForwad);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AMyCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMyCharacter::LookUp);

	// Jump에 대한 Action Binding
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AMyCharacter::StartJump);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Released, this, &AMyCharacter::StopJump);
	PlayerInputComponent->BindAction(TEXT("ViewChange"), EInputEvent::IE_Pressed, this, &AMyCharacter::ViewChange);
}

float AMyCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	// 액터의 기능 중, Can be Damaged이란 속성을 false로 설정하면 데미지 결과가 0으로 설정되 무적 상태가 될 수 있다.
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	ABLOG(Warning, TEXT("Actor : %s took Damage : %f"), *GetName(), FinalDamage);

	//Damaged(FinalDamage);

	CharacterStat->SetDamage(FinalDamage);

	return FinalDamage;
}

bool AMyCharacter::CanSetWeapon()
{
	return (nullptr == CurrentWeapon);
}

void AMyCharacter::SetWeapon(AMyWeapon* NewWeapon)
{
	ABCHECK(nullptr != NewWeapon && nullptr == CurrentWeapon);
	FName WeaponSocket(TEXT("myWeapon_r"));
	if (nullptr != NewWeapon)
	{
		NewWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
		NewWeapon->SetOwner(this);
		CurrentWeapon = NewWeapon;
	}
}

void AMyCharacter::ViewChange()
{
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		GetController()->SetControlRotation(GetActorRotation());
		SetControlMode(EControlMode::DIABLO);
		break;
	case EControlMode::DIABLO:
		GetController()->SetControlRotation(SpringArm->RelativeRotation);
		SetControlMode(EControlMode::GTA);
		break;
	}
}

void AMyCharacter::Attack()
{
	ABLOG(Warning, TEXT("IsAttacking %s : , CurrentCombo : %d"), IsAttacking ? TEXT("true") : TEXT("false"), CurrentCombo);
	if (IsAttacking)
	{
		ABCHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 1, MaxCombo));
		if (CanNextCombo)
		{
			IsComboInputOn = true;
		}
	}
	else
	{
		ABCHECK(CurrentCombo == 0);
		AttackStartComboState();
		AnimInstance->PlayAttackMontage();
		AnimInstance->JumpToAttackMontageSection(CurrentCombo);
		IsAttacking = true;
	}
}

void AMyCharacter::AttackCheck()
{
	ABLOG(Warning, TEXT("ATtackCheck()"));
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(AttackRadius),
		Params
	);

#if ENABLE_DRAW_DEBUG

	FVector TraceVec = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 5.0f;

	DrawDebugCapsule(GetWorld(),
		Center,
		HalfHeight,
		AttackRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime);

#endif

	if (bResult)
	{
		if (HitResult.Actor.IsValid())
		{
			ABLOG(Warning, TEXT("Hit Actor Name : %s"), *HitResult.Actor->GetName());

			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(CharacterStat->GetAttack(), DamageEvent, GetController(), this);			// Params : DamageAmount, DamageEvent, EventInstigator, DamageCauser
		}
	}
}

void AMyCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	ABCHECK(IsAttacking);
	ABCHECK(CurrentCombo > 0);
	IsAttacking = false;
	AttackEndComboState();
}

void AMyCharacter::AttackStartComboState()
{
	CanNextCombo = true;
	IsComboInputOn = false;
	ABCHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 0, MaxCombo - 1));
	CurrentCombo = FMath::Clamp(CurrentCombo + 1, 0, MaxCombo);
}

void AMyCharacter::AttackEndComboState()
{
	IsComboInputOn = false;
	CanNextCombo = false;
	CurrentCombo = 0;
}

void AMyCharacter::MoveForwad(float NewAxisValue)
{
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		// 컨트롤 회전값으로부터 시선 방향과 우측 방향의 벡터 값을 가져오는 코드 (문제있음...)
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);
		break;
	case EControlMode::DIABLO:
		DirectionToMove.X = NewAxisValue;
		break;
	}
	//AddMovementInput(GetActorForwardVector(), NewAxisValue);
}

void AMyCharacter::MoveRight(float NewAxisValue)
{
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		// 컨트롤 회전값으로부터 시선 방향과 우측 방향의 벡터 값을 가져오는 코드 (문제있음...)
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
		break;
	case EControlMode::DIABLO:
		DirectionToMove.Y = NewAxisValue;
		break;
	}
	//AddMovementInput(GetActorRightVector(), NewAxisValue);
}

void AMyCharacter::Turn(float NewAxisValue)
{
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		AddControllerYawInput(NewAxisValue);
		break;
	}
}

void AMyCharacter::LookUp(float NewAxisValue)
{
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		AddControllerPitchInput(NewAxisValue);
		break;
	}
}

void AMyCharacter::StartJump()
{
	// bPressedJump 변수는 Character.h에 정의되있는 bool형 변수.
	bPressedJump = true;
}

void AMyCharacter::StopJump()
{
	bPressedJump = false;
}

void AMyCharacter::SetControlMode(EControlMode NewControlMode)
{
	CurrentControlMode = NewControlMode;

	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		ArmLengthTo = 450.0f;
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritRoll = true;
		SpringArm->bInheritYaw = true;
		SpringArm->bDoCollisionTest = true;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;

	case EControlMode::DIABLO:
		ArmLengthTo = 800.0f;
		ArmRotationTo = FRotator(-45.0f, 0.0f, 0.0f);
		SpringArm->bUsePawnControlRotation = false;
		SpringArm->bInheritPitch = false;
		SpringArm->bInheritRoll = false;
		SpringArm->bInheritYaw = false;
		SpringArm->bDoCollisionTest = false;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;
	}
}



// 데미지 손상 현재 체력 -
void AMyCharacter::Damaged(float point)
{	
	CurrentHpPoint -= point;

	if (CurrentHpPoint < 0)
	{
		CurrentHpPoint = 0;
	}
}

// 체력 회복 현재 체력 +
void AMyCharacter::HPRestore(float point)
{
	CurrentHpPoint += point;
	
	if (CurrentHpPoint > MaxHpPoint)
	{
		CurrentHpPoint = MaxHpPoint;
	}
}

bool AMyCharacter::MpUse(float point)
{
	if (CurrentMpPoint < point)
	{
		// 마나 부족
		return false;
	}
	else
	{
		// 스킬 사용
		CurrentMpPoint -= point;
		return true;
	}
}

void AMyCharacter::MPRestore(float point)
{
	CurrentMpPoint += point;

	if (CurrentMpPoint > MaxMpPoint)
	{
		CurrentMpPoint = MaxMpPoint;
	}
}


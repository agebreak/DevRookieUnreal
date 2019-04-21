// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class PROJECTDRU_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void Attack();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	void AttackStartComboState();
	void AttackEndComboState();

	void MoveForwad(float NewAxisValue);
	void MoveRight(float NewAxisValue);
	void Turn(float NewAxisValue);
	void LookUp(float NewAxisValue);
	void StartJump();
	void StopJump();

	/// [노대영] HP / MP 관련 함수 - Begin

	// 체력 관련 함수
	void Damaged(float point); // 데미지 계산 값이 0 이하시 true 반환

	void HPRestore(float point); // 체력 회복

	////void HpUse(float point); // 체력 소비 스킬 사용 추후에

	// 마나 관련 함수
	bool MpUse(float point); // 마나 사용 함수 <return> true = 스킬 사용 가능 false = 마나 부족

	void MPRestore(float ponint); // 마나 회복 함수 최대 마나치 까지 회복 가능 

	/// [노대영] HP / MP 관련 함수 - End

protected:
	UPROPERTY(VisibleAnywhere, Category=Camera)
	class USpringArmComponent* SpringArm; 

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsAttacking = false;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool CanNextCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsComboInputOn;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 CurrentCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 MaxCombo = 4;

	UPROPERTY()
	class UMyAnimInstance* AnimInstance;

	
	/// [노대영] HP / MP 관련 속성 - Begin

	bool IsDie = false; // 죽었는지 체크

	// 체력 관련
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hp")
		float CurrentHpPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hp")
		float MaxHpPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hp")
		float HpPercent;

	// 체력 초당 회복
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hp")
		float HpRestorePerSecond;*/

	// 마나 관련
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mp")
		float CurrentMpPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mp")
		float MaxMpPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mp")
		float MpPercent;

	// 마나 초당 회복
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mp")
		float MpRestorePerSecond;

	/// [노대영] HP / MP 관련 속성 - End

};

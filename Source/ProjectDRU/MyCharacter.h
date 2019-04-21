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

	/// [��뿵] HP / MP ���� �Լ� - Begin

	// ü�� ���� �Լ�
	void Damaged(float point); // ������ ��� ���� 0 ���Ͻ� true ��ȯ

	void HPRestore(float point); // ü�� ȸ��

	////void HpUse(float point); // ü�� �Һ� ��ų ��� ���Ŀ�

	// ���� ���� �Լ�
	bool MpUse(float point); // ���� ��� �Լ� <return> true = ��ų ��� ���� false = ���� ����

	void MPRestore(float ponint); // ���� ȸ�� �Լ� �ִ� ����ġ ���� ȸ�� ���� 

	/// [��뿵] HP / MP ���� �Լ� - End

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

	
	/// [��뿵] HP / MP ���� �Ӽ� - Begin

	bool IsDie = false; // �׾����� üũ

	// ü�� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hp")
		float CurrentHpPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hp")
		float MaxHpPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hp")
		float HpPercent;

	// ü�� �ʴ� ȸ��
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hp")
		float HpRestorePerSecond;*/

	// ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mp")
		float CurrentMpPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mp")
		float MaxMpPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mp")
		float MpPercent;

	// ���� �ʴ� ȸ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mp")
		float MpRestorePerSecond;

	/// [��뿵] HP / MP ���� �Ӽ� - End

};

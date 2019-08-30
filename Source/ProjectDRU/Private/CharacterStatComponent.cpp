// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterStatComponent.h"
#include "DRUGameInstance.h"

// Sets default values for this component's properties
UCharacterStatComponent::UCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	Level = 1;
}


// Called when the game starts
void UCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetNewLevel(Level);
}

void UCharacterStatComponent::SetNewLevel(int32 NewLevel)
{
	auto DRUGameInstance = Cast<UDRUGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	ABCHECK(nullptr != DRUGameInstance);
	CurrentStatData = DRUGameInstance->GetDRUCharacterData(NewLevel);
	ABLOG(Warning, TEXT(" NewLevel : %d, MaxHp : %f "), NewLevel, CurrentStatData->MaxHP)
	if (nullptr != CurrentStatData)
	{
		Level = NewLevel;
		SetHP(CurrentStatData->MaxHP);
		CurrentHP = CurrentStatData->MaxHP;
	}
	else
	{
		ABLOG(Error, TEXT("Level (%d) data doesn't exist"), NewLevel);
	}
}

void UCharacterStatComponent::SetDamage(float NewDamage)
{
	ABCHECK(nullptr != CurrentStatData);
	SetHP(FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, CurrentStatData->MaxHP));
	ABLOG(Warning, TEXT("SetDamage damage %f"), NewDamage);
}

void UCharacterStatComponent::SetHP(float NewHP)
{
	ABLOG(Warning, TEXT("SetHP NewHP %f, CurrentHp : %f"), NewHP, CurrentHP);
	CurrentHP = NewHP;
	OnHpChanged.Broadcast();
	ABLOG(Warning, TEXT("CurrentHP < KINDA_SMALL_NUMBER ? %s"), (CurrentHP < KINDA_SMALL_NUMBER) ? TEXT("TRUE") : TEXT("FALSE"));
	if (CurrentHP < KINDA_SMALL_NUMBER)				// KINDA_SMALL_NUMBER 는 언리얼에서 제공하는 매크로로, float의 값을 0과 비교할 때 미세한 오차 범위를 무시하고 측정할 수 있도록 제공.
	{
		CurrentHP = 0.0f;
		OnHPIsZero.Broadcast();
	}
}

float UCharacterStatComponent::GetAttack()
{
	ABCHECK(nullptr != CurrentStatData, 0.0f);
	return CurrentStatData->Attack;
}

float UCharacterStatComponent::GetHPRatio()
{
	ABCHECK(nullptr != CurrentStatData, 0.0f);

	return (CurrentStatData->MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentHP / CurrentStatData->MaxHP);
}





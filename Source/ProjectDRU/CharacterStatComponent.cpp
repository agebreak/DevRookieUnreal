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
	if (nullptr != CurrentStatData)
	{
		Level = NewLevel;
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
	CurrentHP = FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, CurrentStatData->MaxHP);

	if (CurrentHP <= 0.0f)
	{
		OnHPIsZero.Broadcast();
	}
}

float UCharacterStatComponent::GetAttack()
{
	ABCHECK(nullptr != CurrentStatData, 0.0f);
	return CurrentStatData->Attack;
}





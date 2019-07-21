// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectDRU.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "DRUGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FDRUCharacterData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FDRUCharacterData() : Level(1), MaxHP(100.0f), Attack(10.0f), DropExp(10), NextExp(30) {}

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Data")
		int32 Level;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Data")
		float MaxHP;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Data")
		float Attack;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Data")
		int32 DropExp;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Data")
		int32 NextExp;
};

/**
 * 
 */
UCLASS()
class PROJECTDRU_API UDRUGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UDRUGameInstance();

	virtual void Init() override;
	FDRUCharacterData* GetDRUCharacterData(int32 Level);

private:
	UPROPERTY()
		class UDataTable* ADRUCharacterTable;
	
};

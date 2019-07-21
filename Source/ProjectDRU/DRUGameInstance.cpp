// Fill out your copyright notice in the Description page of Project Settings.


#include "DRUGameInstance.h"

UDRUGameInstance::UDRUGameInstance()
{
	FString CharacterDataPath = TEXT("/Game/Book/GameData/DRUCharacterData.DRUCharacterData");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_DRUCHARACTER(*CharacterDataPath);
	ABCHECK(DT_DRUCHARACTER.Succeeded());
	ADRUCharacterTable = DT_DRUCHARACTER.Object;
	ABCHECK(ADRUCharacterTable->GetRowMap().Num() > 0);
}

void UDRUGameInstance::Init()
{
	Super::Init();

	//ABLOG(Warning, TEXT("DropExp of Level 20 ADRUCHARACTER : %d"), GetDRUCharacterData(20)->DropExp);
}

FDRUCharacterData * UDRUGameInstance::GetDRUCharacterData(int32 Level)
{
	return ADRUCharacterTable->FindRow<FDRUCharacterData>(*FString::FromInt(Level), TEXT(""));
}

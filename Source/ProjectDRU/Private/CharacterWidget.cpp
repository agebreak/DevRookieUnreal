// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterWidget.h"
#include "CharacterStatComponent.h"
#include "Components/ProgressBar.h"

void UCharacterWidget::BindCharacterStat(UCharacterStatComponent* NewCharacterStat)
{
	ABCHECK(nullptr != NewCharacterStat);
	ABLOG(Warning, TEXT("BindCharacterStat"));
	CurrentCharacterStat = NewCharacterStat;
	CurrentCharacterStat->OnHpChanged.AddUObject(this, &UCharacterWidget::UpdateHPWidget);
}

void UCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ABLOG(Warning, TEXT("NativeConstruct"));
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
	ABCHECK(nullptr != HPProgressBar);
	UpdateHPWidget();
}

void UCharacterWidget::UpdateHPWidget()
{
	ABLOG(Warning, TEXT("UpdateHPWidget"));
	ABLOG(Warning, TEXT("CurrentCharacterStat.IsValid() ? %s"), (CurrentCharacterStat.IsValid()) ? TEXT("TRUE") : TEXT("FALSE"));
;	if (CurrentCharacterStat.IsValid())
	{
	ABLOG(Warning, TEXT("nullptr != HPProgressBar ? %s"), (nullptr != HPProgressBar) ? TEXT("TRUE") : TEXT("FALSE"));
		if (nullptr != HPProgressBar)
		{
			HPProgressBar->SetPercent(CurrentCharacterStat->GetHPRatio());
		}
	}
}

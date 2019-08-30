// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"

void AMyPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABLOG(Warning, TEXT("PostInitializeComponents"));
}

void AMyPlayerController::OnPossess(APawn * aPawn)
{
	ABLOG(Warning, TEXT("OnPossess"));
	Super::OnPossess(aPawn);
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
}

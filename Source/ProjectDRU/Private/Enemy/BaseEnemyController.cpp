// Fill out your copyright notice in the Description page of Project Settings.

#include "./Public/Enemy/BaseEnemyController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

void ABaseEnemyController::BeginPlay()
{
	Super::BeginPlay();

	if (nullptr == MoveTargetActor)
	{
		MoveTargetActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	}
}

void ABaseEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (nullptr != MoveTargetActor)
	{
		MoveToActor(MoveTargetActor, 10.f);
	}

}
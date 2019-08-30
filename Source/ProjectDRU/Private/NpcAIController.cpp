// Fill out your copyright notice in the Description page of Project Settings.

#include "NpcAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName ANpcAIController::HomePosKey(TEXT("HomePos"));
const FName ANpcAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName ANpcAIController::TargetKey(TEXT("Target"));

ANpcAIController::ANpcAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/Book/AI/BB_NPC.BB_NPC"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}
	ABLOG(Error, TEXT("BBObject.Succeeded() %d"), BBObject.Succeeded());
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/Book/AI/BT_NPC.BT_NPC"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
	ABLOG(Error, TEXT("BBObject.Succeeded() %d"), BTObject.Succeeded());
}

void ANpcAIController::OnPossess(APawn * InPawn)
{
	Super::Possess(InPawn);

	if (UseBlackboard(BBAsset, Blackboard))
	{
		Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BTAsset))
		{
			ABLOG(Error, TEXT("AIController couldn't run behavior tree!"));
		}
	}
	//GetWorld()->GetTimerManager().SetTimer(RepeatTimerHandle, this, &ANpcAIController::OnRepeatTimer, RepeatInterval, true);
}

void ANpcAIController::OnUnPossess()
{
	Super::UnPossess();
}
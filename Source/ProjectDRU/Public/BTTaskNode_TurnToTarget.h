// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectDRU.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_TurnToTarget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDRU_API UBTTaskNode_TurnToTarget : public UBTTaskNode
{
	GENERATED_BODY()
	

public:
	UBTTaskNode_TurnToTarget();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

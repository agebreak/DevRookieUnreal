// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ProjectDRU.h"
#include "GameFramework/GameModeBase.h"
#include "ProjectDRUGameMode.generated.h"

UCLASS(minimalapi)
class AProjectDRUGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AProjectDRUGameMode(const FObjectInitializer& ObjectInitializer);
	virtual void PostLogin(APlayerController* NewPlayer) override;
};




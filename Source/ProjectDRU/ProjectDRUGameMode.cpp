// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ProjectDRUGameMode.h"
#include "ProjectDRUPlayerController.h"
#include "ProjectDRUCharacter.h"
#include "MyPlayerController.h"
#include "MyCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectDRUGameMode::AProjectDRUGameMode()
{
	// use our custom PlayerController class	
	PlayerControllerClass = AMyPlayerController::StaticClass();

	static ConstructorHelpers::FClassFinder<AMyCharacter> PAWN(TEXT("Blueprint'/Game/Blueprint/MyCharacter_BP.MyCharacter_BP_C'"));
	DefaultPawnClass = PAWN.Class;
}
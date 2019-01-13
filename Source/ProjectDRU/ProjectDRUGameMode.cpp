// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ProjectDRUGameMode.h"
#include "ProjectDRUPlayerController.h"
#include "ProjectDRUCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectDRUGameMode::AProjectDRUGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AProjectDRUPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
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

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT(
	"/Game/Blueprint/MyCharacter_BP.MyCharacter_BP_C"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
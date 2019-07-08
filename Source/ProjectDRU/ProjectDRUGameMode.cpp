// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ProjectDRUGameMode.h"
#include "ProjectDRUPlayerController.h"
#include "ProjectDRUCharacter.h"
#include "MyPlayerController.h"
#include "MyCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine.h"

AProjectDRUGameMode::AProjectDRUGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// use our custom PlayerController class	
	PlayerControllerClass = AMyPlayerController::StaticClass();

	static ConstructorHelpers::FClassFinder<AMyCharacter> PAWN(TEXT("Blueprint'/Game/Blueprint/MyCharacter_BP.MyCharacter_BP_C'"));

	if (PAWN.Class != NULL)
	{
		DefaultPawnClass = PAWN.Class;
	}
}

void AProjectDRUGameMode::PostLogin(APlayerController * NewPlayer)
{
	ABLOG(Warning, TEXT("PostLogin Begin"));
	Super::PostLogin(NewPlayer);
	ABLOG(Warning, TEXT("PostLogin End"));
}

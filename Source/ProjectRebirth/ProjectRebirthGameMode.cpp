// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectRebirthGameMode.h"
#include "ProjectRebirthCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectRebirthGameMode::AProjectRebirthGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

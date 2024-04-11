// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoint.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
	CheckpointBounds = CreateDefaultSubobject<UBoxComponent>("Checkpoint bounds");
	RootComponent = CheckpointBounds;
}






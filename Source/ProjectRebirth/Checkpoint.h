// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Checkpoint.generated.h"

UCLASS()
class PROJECTREBIRTH_API ACheckpoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckpoint();

	UPROPERTY(VisibleAnywhere) UBoxComponent* CheckpointBounds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int CheckpointIndex;

};

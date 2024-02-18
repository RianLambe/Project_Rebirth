// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "AudioPlayer.generated.h"

UCLASS()
class PROJECTREBIRTH_API AAudioPlayer : public AActor
{
	GENERATED_BODY()
	
public:
	UFUNCTION() void PlayAudio(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	// Sets default values for this actor's properties
	AAudioPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere) UBoxComponent* Bounds;
	UPROPERTY() UAudioComponent* AudioComp;
	
	UPROPERTY(EditAnywhere) USoundBase* Audio;
	UPROPERTY(EditAnywhere, meta=(ClampMin = 0, ClampMax = 100)) int ChanceToPlay;
};

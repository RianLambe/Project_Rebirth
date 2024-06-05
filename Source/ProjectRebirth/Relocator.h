// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Relocator.generated.h"


class AProjectRebirthCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTREBIRTH_API URelocator : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URelocator();

	UFUNCTION(BlueprintCallable) void RelocatePlayer(FTransform NewTransform);
	UFUNCTION(BlueprintCallable) void FreezePlayer(bool Freeze);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	AProjectRebirthCharacter* PlayerRef;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

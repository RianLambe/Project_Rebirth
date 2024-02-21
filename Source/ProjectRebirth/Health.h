// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Health.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTREBIRTH_API UHealth : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealth();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable) void DecrementHealth(float amount);
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float Health = 100;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) bool DestroyOnDeath = true;
};

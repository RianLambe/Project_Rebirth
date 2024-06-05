// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDied);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTREBIRTH_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable) void DecrementHealth(float amount);
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float Health = 100;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) bool DestroyOnDeath = true;
	
	UPROPERTY(BlueprintAssignable, VisibleAnywhere) FOnDied Died;

};

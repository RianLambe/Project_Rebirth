// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interaction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteract);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTREBIRTH_API UInteraction : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteraction();

	UPROPERTY(BlueprintAssignable, VisibleAnywhere) FOnInteract OnInteract;
	UFUNCTION(BlueprintCallable) void Interact();
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float MaxInteractDistance = 300;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) bool DebugEnabled = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere) FVector NewPosition;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) FRotator NewRotation;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere) bool CanInteract = true;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

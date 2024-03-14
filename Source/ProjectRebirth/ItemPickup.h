// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemHandeler.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "ItemPickup.generated.h"

UCLASS()
class PROJECTREBIRTH_API AItemPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void OnConstruction(const FTransform &Transform) override;

	UPROPERTY() UBoxComponent* ItemCollider;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere) FName Item;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UDataTable* ItemData;
	FItemStruct* currentItemData;
	UPROPERTY(EditAnywhere) USkeletalMeshComponent* ItemPickupMesh;
	UPROPERTY(EditAnywhere) bool ItemPhysics = true;
};

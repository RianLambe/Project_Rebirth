// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IDetailCustomization.h"
#include "IDetailChildrenBuilder.h"
#include "DetailLayoutBuilder.h"
#include "PropertyHandle.h"

#include "CoreMinimal.h"
#include "ItemHandeler.h"
#include "SGraphPinDataTableRowName.h"
#include "Components/BoxComponent.h"
#include "Elements/Common/TypedElementHandles.h"
#include "GameFramework/Actor.h"
#include "ItemPickup.generated.h"



UCLASS()
class PROJECTREBIRTH_API AItemPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemPickup();

	//Exposed properties


	UPROPERTY(EditAnywhere) FDataTableRowHandle Items;
	FDataTableRowHandle RowHandle;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) FName Item;
	UPROPERTY(EditAnywhere) bool ItemPhysics = true;

protected:
	// Called when the game starts or when spawned
	virtual void OnConstruction(const FTransform &Transform) override;

	//Protected variables
	UPROPERTY() UDataTable* ItemData;
	FItemStruct* CurrentItemData;

	//Objects
	UPROPERTY() USceneComponent* PickupRoot;
	UPROPERTY() USkeletalMeshComponent* ItemPickupMesh;
	UPROPERTY() UBoxComponent* ItemCollider;
};

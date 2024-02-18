// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemPickup.h"
#include "ItemHandeler.h"

// Sets default values
AItemPickup::AItemPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	ItemPickupMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Item pickup mesh");
	RootComponent = ItemPickupMesh;

}

// Called when the game starts or when spawned
void AItemPickup::BeginPlay()
{
	Super::BeginPlay();
	const FString ContextString; 
	currentItemData = ItemData->FindRow<FItemStruct>(Item, ContextString);

	if (currentItemData) {
		GEngine->AddOnScreenDebugMessage(0, 5, FColor::Red, "Found data");
		USkeletalMesh* test = currentItemData->ItemMesh;
		GEngine->AddOnScreenDebugMessage(0, 5, FColor::Red, currentItemData->ItemMesh->GetName());
		
		ItemPickupMesh->SetSkeletalMesh(currentItemData->ItemMesh);
	}


}

// Called every frame
void AItemPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


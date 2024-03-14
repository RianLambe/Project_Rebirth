// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemPickup.h"
#include "ItemHandeler.h"

// Sets default values
AItemPickup::AItemPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* r = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(r);
	
	ItemPickupMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Item pickup mesh");
	ItemPickupMesh->SetupAttachment(r);

	ItemCollider = CreateDefaultSubobject<UBoxComponent>("Item collision");
	ItemCollider->SetupAttachment(ItemPickupMesh);

}

// Called when the game starts or when spawned
void AItemPickup::BeginPlay()
{
	ItemPickupMesh->SetSimulatePhysics(true);
}

//Setup pickup on object construction
void AItemPickup::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (ItemData) {
		const FString ContextString; 
		currentItemData = ItemData->FindRow<FItemStruct>(Item, ContextString);

		if (currentItemData) {

			ItemPickupMesh->SetSkeletalMesh(currentItemData->ItemMesh);
			ItemCollider->InitBoxExtent(currentItemData->ColliderSize);
			ItemCollider->SetRelativeLocation(currentItemData->ColliderOffset);
		}
	}
}

// Called every frame
void AItemPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


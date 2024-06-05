// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemPickup.h"

// Sets default values
AItemPickup::AItemPickup() {
	
	//Item mesh
	ItemPickupMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Item pickup mesh");
	ItemPickupMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ItemPickupMesh->SetSimulatePhysics(true);
	SetRootComponent(ItemPickupMesh);

	//Item collider
	ItemCollider = CreateDefaultSubobject<UBoxComponent>("Item collision");
	ItemCollider->SetupAttachment(ItemPickupMesh);

	ItemCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ItemCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
	ItemCollider->SetCollisionProfileName(FName("BlockAll"));

	
	//Finds a reference to the item data table in the project
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableFinder(TEXT("/Script/Engine.DataTable'/Game/Items/ItemData.ItemData'"));
	if (DataTableFinder.Succeeded()) {
		ItemData1 = DataTableFinder.Object;
	}
}

//Setup pickup on object construction
void AItemPickup::OnConstruction(const FTransform& Transform) {
	
	Super::OnConstruction(Transform);

	//Find data at row location
	if (ItemData.DataTable) {
		const FString ContextString; 
		CurrentItemData = ItemData.DataTable->FindRow<FItemStruct>(ItemData.RowName, ContextString);
		
		//Assign parameters if item data has been found
		if (CurrentItemData) {
			ItemPickupMesh->SetSkeletalMesh(CurrentItemData->ItemMesh);
			ItemCollider->InitBoxExtent(CurrentItemData->ColliderSize);
			ItemCollider->SetRelativeLocation(CurrentItemData->ColliderOffset);
		}
	}
}


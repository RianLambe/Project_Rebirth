// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemHandeler.h"
#include "ContentBrowserItemData.h"
#include "Health.h"
#include "HealthComponent.h"
#include "K2Node_AddComponentByClass.h"
#include "ProjectRebirthCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/GameSession.h"
#include "Engine/DataTable.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SkeletalMeshComponent.h"


// Sets default values for this component's properties
UItemHandeler::UItemHandeler() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//NewSkeletalMeshComponent->SetupAttachment(playerActor->GetRootComponent());

	//ItemMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Item mesh");
	//ItemMesh->SetRelativeLocation(FVector(0,0,-150));
}

// Called when the game starts
void UItemHandeler::BeginPlay() {
	Super::BeginPlay();

	playerActor = GetOwner();
	//camera =

	// ...
}

// Called every frame
void UItemHandeler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

//Sets the current item
void UItemHandeler::SetCurrentItem(FName item) {
	const FString ContextString; 

	
	currentItemData = itemData->FindRow<FItemStruct>(item, ContextString);
	if (currentItemData) {
		if (DebugEnabled) GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, "New item set too : " + currentItemData->ItemName);

		// Create the new Skeletal Mesh Component
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, "Item not found");
	}
}


//Uses the current item
void UItemHandeler::UseItem() {
	//Escape from function if requirements not met 
	if (GetWorld()->GetTimeSeconds() - TimeSinceUse < 1 / currentItemData->FireRate) return void();
	if (!currentItemData) return void();

	OnMyCustomEvent.Broadcast();
	
	//track time since the last use of the item
	TimeSinceUse = GetWorld()->GetTimeSeconds();
	
	//Local variables for line trace
	FVector TraceStart;
	FVector TraceEnd;
	FVector CameraRotation;
	FHitResult HitResult;
	UCameraComponent* CameraRef = playerActor->FindComponentByClass<UCameraComponent>();

	//Calculations for line trace
	TraceStart = CameraRef->GetComponentLocation();
	CameraRotation = CameraRef->GetComponentRotation().Vector();
	TraceEnd = TraceStart + (CameraRotation * 50000);

	//Play shoot sound
	UGameplayStatics::PlaySoundAtLocation(this, currentItemData->ItemUseSound, TraceStart);
	
	//Do line trace
	if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility)) {
		UNiagaraComponent* NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), currentItemData->HitParticleSystem, HitResult.Location, HitResult.Normal.ToOrientationRotator());

		UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(HitResult.GetActor()->GetRootComponent());

		// Apply the impulse 
		if(HitResult.GetComponent()->IsSimulatingPhysics()) HitResult.Component->AddImpulse(playerActor->GetActorForwardVector() * currentItemData->ImpulseForce, "", true);

		//Apply damage
		if(HitResult.GetActor()->GetComponentByClass<UHealthComponent>()) {
			HitResult.GetActor()->GetComponentByClass<UHealthComponent>()->DecrementHealth(50);
		}
		
	}
	//If line trace returns null
	else {
		GEngine->AddOnScreenDebugMessage(-1, GetWorld()->GetDeltaSeconds(), FColor::Red, "You did not hit anything");
	}

	//Debug
	if (DebugEnabled) DrawDebugLine(GetWorld(), TraceStart, TraceEnd, currentItemData->DebugTraceColor, false,2.0f,0,1.0f);

}


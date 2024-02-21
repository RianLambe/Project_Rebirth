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
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, "New item set too : " + currentItemData->ItemName);

		// Create the new Skeletal Mesh Component

	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, "Item not found");
	}
}


//Uses the current item
void UItemHandeler::UseItem() {
	if (!currentItemData) return void();

	//Local variables for line trace
	FVector start;
	FVector CameraRotation;
	FVector end;
	FHitResult hitResult;
	UCameraComponent* cameraRef = playerActor->FindComponentByClass<UCameraComponent>();

	//Calculations for line trace
	start = cameraRef->GetComponentLocation();
	CameraRotation = cameraRef->GetComponentRotation().Vector();
	end = start + (CameraRotation * 50000);

	//Play shoot sound
	UGameplayStatics::PlaySoundAtLocation(this, currentItemData->ItemUseSound, start);
	
	//Do line trace
	if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECC_Visibility)) {
		//Debug 
		if(DebugEnabled) DrawDebugLine(GetWorld(), start, hitResult.ImpactPoint, currentItemData->DebugTraceColor, false,2.0f,0,1.0f);

	
		UNiagaraComponent* NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), currentItemData->HitParticleSystem, hitResult.Location, hitResult.Normal.ToOrientationRotator());
		//UParticleSystemComponent* ParticleSystemComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystemAsset, FVector(0,0,0));

		UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(hitResult.GetActor()->GetRootComponent());

		// Apply the impulse 
		if(hitResult.GetComponent()->IsSimulatingPhysics()) hitResult.Component->AddImpulse(playerActor->GetActorForwardVector() * currentItemData->ImpulseForce, "", true);

		//hitResult.GetComponent()->AddImpulse(ImpulseForce * playerActor->GetActorForwardVector());

		//if (Cast<UHealthComponent>(hitResult.GetActor())) GEngine->AddOnScreenDebugMessage(-1, 15, currentItemData->DebugTraceColor,"You hit an object, The name of it is  : " + hitResult.GetActor()->GetName());

		if(hitResult.GetActor()->GetComponentByClass<UHealthComponent>()) {
			hitResult.GetActor()->GetComponentByClass<UHealthComponent>()->DecrementHealth(50);
			//GEngine->AddOnScreenDebugMessage(0, 5, FColor::Red, "Hit");
		}
		

		//Cast<UHealthComponent>(hitResult.GetActor())->DecrementHealth(15);
	}
	//If line trace returns null
	else {
		GEngine->AddOnScreenDebugMessage(-1, GetWorld()->GetDeltaSeconds(), FColor::Red, "You did not hit anything");
		if (DebugEnabled) DrawDebugLine(GetWorld(), start, end, currentItemData->DebugTraceColor, false,2.0f,0,1.0f);
	}
}


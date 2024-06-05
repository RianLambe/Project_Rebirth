// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemHandeler.h"
#include "FPAnimInstance.h"
#include "HealthComponent.h"
#include "ProjectRebirthCharacter.h"
#include "Camera/CameraComponent.h"
#include "Engine/DataTable.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SkeletalMeshComponent.h"
#include "ItemPickup.h"



// Sets default values for this component's properties
UItemHandeler::UItemHandeler() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UItemHandeler::BeginPlay() {
	Super::BeginPlay();

	playerActor = GetOwner();
	ArmsRef = Cast<AProjectRebirthCharacter>(GetOwner())->FPArmsMesh;
	ItemRef = Cast<AProjectRebirthCharacter>(GetOwner())->ItemMesh;
}

// Called every frame
void UItemHandeler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Local variables for line trace
	FVector TraceStart;
	FVector TraceEnd;
	FVector CameraRotation;
	FHitResult InteractResult;
	UCameraComponent* CameraRef = playerActor->FindComponentByClass<UCameraComponent>();
	
	//Calculations for line trace
	TraceStart = CameraRef->GetComponentLocation();
	CameraRotation = CameraRef->GetComponentRotation().Vector();
	TraceEnd = TraceStart + (CameraRotation * maxInteractDistance);

	//Do line trace
	if (GetWorld()->LineTraceSingleByChannel(InteractResult, TraceStart, TraceEnd, ECC_Visibility)) {
		PotentialInteract = InteractResult.GetActor();

		if (Cast<AItemPickup>(InteractResult.GetActor())) {
			//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, InteractResult.GetActor()->GetName());
			PotentialInteract = InteractResult.GetActor();
		}
	}
}

//Sets the current item
void UItemHandeler::SetCurrentItem(FName item) {
	const FString ContextString; 

	//If there is item data found then set all new properties
	if (itemData) {
		currentItemData = itemData->FindRow<FItemStruct>(item, ContextString);
		if (DebugEnabled) GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, "New item set too : " + currentItemData->ItemName);

		if (currentItemData) {
			ItemRef->SetSkeletalMesh(currentItemData->ItemMesh);

			//Set animation controller values for both the item and the arms
			Cast<UFPAnimInstance>(ItemRef->GetAnimInstance())->EquipAnim = currentItemData->EquipAnim.Item; //Equip
			Cast<UFPAnimInstance>(ArmsRef->GetAnimInstance())->EquipAnim = currentItemData->EquipAnim.Arms;
		
			Cast<UFPAnimInstance>(ItemRef->GetAnimInstance())->IdleAnim = currentItemData->IdleAnim.Item; //Idle
			Cast<UFPAnimInstance>(ArmsRef->GetAnimInstance())->IdleAnim = currentItemData->IdleAnim.Arms;

			Cast<UFPAnimInstance>(ItemRef->GetAnimInstance())->ADSAnim = currentItemData->ADSAnim.Item; //ADS
			Cast<UFPAnimInstance>(ArmsRef->GetAnimInstance())->ADSAnim = currentItemData->ADSAnim.Arms;

			Cast<UFPAnimInstance>(ItemRef->GetAnimInstance())->Reset = true;
			Cast<UFPAnimInstance>(ArmsRef->GetAnimInstance())->Reset = true;

			
		}

	}
	else {
		if (DebugEnabled) GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, "Item item data found");
	}
}

//Uses the current item
void UItemHandeler::UseItem() {
	//Escape from function if requirements not met 
	if (!currentItemData) return void();
	if (GetWorld()->GetTimeSeconds() - TimeSinceUse < 1 / currentItemData->FireRate) return void();

	
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

void UItemHandeler::Interact() {

	//if (PotentialInteract) {
	//	SetCurrentItem(Cast<AItemPickup>(PotentialInteract)->ItemData.RowName);
	//	if (DebugEnabled) GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, Cast<AItemPickup>(PotentialInteract)->ItemData.RowName.ToString());
	//}

}


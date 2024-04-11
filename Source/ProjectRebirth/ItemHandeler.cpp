// Fill out your copyright notice in the Description page of Project Settings.

#include "FPAnimInstance.h"
#include "HealthComponent.h"
#include "ProjectRebirthCharacter.h"
#include "Camera/CameraComponent.h"
#include "Engine/DataTable.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SkeletalMeshComponent.h"
#include "ItemHandeler.h"

#include "ItemPickup.h"


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
	ArmsRef = Cast<AProjectRebirthCharacter>(GetOwner())->FPArmsMesh;
	ItemRef = Cast<AProjectRebirthCharacter>(GetOwner())->ItemMesh;

	//camera =

	// ...
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
		if (Cast<AItemPickup>(InteractResult.GetActor())) {
			//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, InteractResult.GetActor()->GetName());
			PotentialInteract = InteractResult.GetActor();
		}
	}
}

//Sets the current item
void UItemHandeler::SetCurrentItem(FName item) {
	const FString ContextString; 

	if (itemData) {
		currentItemData = itemData->FindRow<FItemStruct>(item, ContextString);
		if (DebugEnabled) GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, "New item set too : " + currentItemData->ItemName);

		if (currentItemData) ItemRef->SetSkeletalMesh(currentItemData->ItemMesh);
		Cast<UFPAnimInstance>(ItemRef->GetAnimInstance())->IdleAnim = currentItemData->IdleAnim.Item;
		Cast<UFPAnimInstance>(ArmsRef->GetAnimInstance())->IdleAnim = currentItemData->IdleAnim.Arms;

		// Create the new Skeletal Mesh Component
	}
	else {
		if (DebugEnabled) GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, "Item item data found");
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

void UItemHandeler::Interact() {

	if (PotentialInteract) {
		SetCurrentItem(Cast<AItemPickup>(PotentialInteract)->ItemData.RowName);
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, Cast<AItemPickup>(PotentialInteract)->ItemData.RowName.ToString());
	}

}


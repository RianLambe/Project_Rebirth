// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction.h"

// Sets default values for this component's properties
UInteraction::UInteraction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

//Called when the player pressed the interact button
void UInteraction::Interact() {
	const FVector Start = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation();
	const FVector End = Start + GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraRotation().Vector() * MaxInteractDistance;
	FHitResult Result;

	//Do trace 
	if (GetWorld()->LineTraceSingleByChannel(Result, Start, End, ECC_Visibility) && Result.GetActor()->FindComponentByClass<UInteraction>()) {
		if (DebugEnabled) {
		if (DebugEnabled) DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 2);
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, "You interacted with something " + Result.GetActor()->GetName());
		}
		
		Result.GetActor()->FindComponentByClass<UInteraction>()->OnInteract.Broadcast();
	}
	else {
		if (DebugEnabled) DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2);
	}
}

// Called when the game starts
void UInteraction::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteraction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


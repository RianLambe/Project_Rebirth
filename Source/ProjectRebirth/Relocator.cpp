// Fill out your copyright notice in the Description page of Project Settings.


#include "Relocator.h"

#include "ProjectRebirthCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
URelocator::URelocator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void URelocator::RelocatePlayer(FTransform NewTransform) {
	PlayerRef->GetInstigatorController()->SetControlRotation(NewTransform.Rotator());
	PlayerRef->SetActorLocation(NewTransform.GetLocation());
	PlayerRef->Arms->SetRelativeRotation(FRotator(0,0,0));
}

void URelocator::FreezePlayer(bool Freeze) {
	PlayerRef->CanMove = Freeze;
	PlayerRef->CanLook = Freeze;

}


// Called when the game starts
void URelocator::BeginPlay()
{
	Super::BeginPlay();

	PlayerRef = Cast<AProjectRebirthCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AProjectRebirthCharacter::StaticClass()));

	// ...
	
}


// Called every frame
void URelocator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


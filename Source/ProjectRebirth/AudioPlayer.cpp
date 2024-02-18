// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioPlayer.h"

#include "ProjectRebirthCharacter.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AAudioPlayer::AAudioPlayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Bounds = CreateDefaultSubobject<UBoxComponent>("Bounds");
	Bounds->SetBoxExtent(FVector(130, 75, 150));
	SetRootComponent(Bounds);
	
	AudioComp = CreateDefaultSubobject<UAudioComponent>("Sound");
	
}


// Called when the game starts or when spawned
void AAudioPlayer::BeginPlay()
{
	Super::BeginPlay();
	Bounds->OnComponentBeginOverlap.AddDynamic(this, &AAudioPlayer::PlayAudio);

}

// Called every frame
void AAudioPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAudioPlayer::PlayAudio(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
	if (FMath::RandRange(1, 100) <= ChanceToPlay) {
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, OtherComp->GetName());
		AudioComp->Sound = Audio;
		AudioComp->Play();
	}
}




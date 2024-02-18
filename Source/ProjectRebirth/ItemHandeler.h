// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Components/SkeletalMeshComponent.h"
#include "NiagaraSystem.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "ItemHandeler.generated.h"

USTRUCT(BlueprintType)
struct FItemStruct : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual") FString ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual") UTexture* ItemImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual") USkeletalMesh* ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General") float ImpulseForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General") float FireRate;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds") USoundBase* ItemUseSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds") USoundBase* ItemHitSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particals") UNiagaraSystem* HitParticleSystem;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particals") UParticleSystem* ParticleSystemAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug") FColor DebugTraceColor;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTREBIRTH_API UItemHandeler : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemHandeler();



protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Functions
	UFUNCTION(BlueprintCallable) void SetCurrentItem(FName item);

  	UPROPERTY(BlueprintReadWrite, EditAnywhere) float maxInteractDistance;
	void UseItem();

	
	//Variables
	UPROPERTY()
	AActor* playerActor;

	UPROPERTY()
	USkeletalMeshComponent* currentItemMesh;
	
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* NewSkeletalMeshComponent;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UDataTable* itemData;
	FItemStruct* currentItemData;

	UPROPERTY(BlueprintReadWrite, EditAnywhere) bool DebugEnabled;

	
};
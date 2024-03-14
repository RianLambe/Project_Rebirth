// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Components/SkeletalMeshComponent.h"
#include "NiagaraSystem.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "ItemHandeler.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMyCustomDelegate);

//Struct settups 
USTRUCT(BlueprintType)
struct FAnimations : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite,EditAnywhere) UAnimMontage* Arms;
	UPROPERTY(BlueprintReadWrite,EditAnywhere) UAnimMontage* Item;
};

USTRUCT(BlueprintType)
struct FItemStruct : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,  Category = "Visual") FString ItemName;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,  Category = "Visual") UTexture* ItemImage;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,  Category = "Visual") USkeletalMesh* ItemMesh;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,  Category = "Animation") FAnimations EquipAnim;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,  Category = "Animation") FAnimations IdleAnim;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,  Category = "Animation") FAnimations ADSAnim;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,  Category = "Animation") FAnimations HipFireAnim;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,  Category = "General") float ImpulseForce;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,  Category = "General") float FireRate = 1;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,  Category = "Sounds") USoundBase* ItemUseSound;
	UPROPERTY(BlueprintReadWrite, EditAnywhere,  Category = "Sounds") USoundBase* ItemHitSound;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,  Category = "Particals") UNiagaraSystem* HitParticleSystem;
	UPROPERTY(BlueprintReadWrite, EditAnywhere,  Category = "Particals") UParticleSystem* ParticleSystemAsset;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,  Category = "Pickup") FVector ColliderSize = FVector(15, 25, 20);
	UPROPERTY(BlueprintReadWrite, EditAnywhere,  Category = "Pickup") FVector ColliderOffset;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,  Category = "Debug") FColor DebugTraceColor;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTREBIRTH_API UItemHandeler : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemHandeler();

	UPROPERTY(BlueprintAssignable, Category = "MyCategory")
	FMyCustomDelegate OnMyCustomEvent;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	float TimeSinceUse;

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
	UPROPERTY(BlueprintReadWrite,EditAnywhere,  Category = "MyCategory|SubCategory") UAnimMontage* ArmsShootAnim;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* NewSkeletalMeshComponent;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UDataTable* itemData;
	FItemStruct* currentItemData;

	UPROPERTY(BlueprintReadWrite, EditAnywhere) bool DebugEnabled;
	
	
};
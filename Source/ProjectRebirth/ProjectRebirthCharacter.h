// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "ProjectRebirthCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AProjectRebirthCharacter : public ACharacter
{
	GENERATED_BODY()
	
	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FireAction;
	
public:
	AProjectRebirthCharacter();

	UPROPERTY(BlueprintReadWrite, EditAnywhere) bool CanMove = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) bool CanLook = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) bool ADS;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player settings") float LookSensitivity = 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player settings") float ADSSensitivityPercent = .5;


protected:
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime);

public:
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh)
	USkeletalMeshComponent* FPArmsMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite) USoundBase* hitSound;

	
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	/** Setter to set the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) FRotator FPArmsTargetRot = FRotator(0,-90,0);

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	bool RecenterView;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	void Fire();
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	//USkeletalMeshComponent* GetMesh1P() const { return FPArms; }
	/** Returns FirstPersonCameraComponent subobject **/
	//UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	UPROPERTY(EditAnywhere, BlueprintReadOnly) USceneComponent* Arms;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* AdditionalMeshComponent;

	UPROPERTY(BlueprintReadOnly, EditAnywhere) USkeletalMeshComponent* ItemMesh;
};


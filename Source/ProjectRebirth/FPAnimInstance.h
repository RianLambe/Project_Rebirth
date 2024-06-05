// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FPAnimInstance.generated.h"

UENUM(BlueprintType)
enum AnimStates {Default, Skydiving, Misc};

UCLASS()
class PROJECTREBIRTH_API UFPAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public :
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) UAnimSequence* EquipAnim;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) UAnimSequence* IdleAnim;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) UAnimSequence* ADSAnim;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) TEnumAsByte<AnimStates> AnimState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector2D LookDirection;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool IsAiming;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool Reset;

	UFUNCTION(BlueprintImplementableEvent) void ResetAnimState();
	
};

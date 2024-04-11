// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FPAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTREBIRTH_API UFPAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public :
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) UAnimSequence* IdleAnim;
};

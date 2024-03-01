// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectRebirthCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "ProjectRebirthProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "ItemHandeler.h"
#include "AssetTypeActions/AssetDefinition_SoundBase.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AProjectRebirthCharacter

AProjectRebirthCharacter::AProjectRebirthCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	//FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	//FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	//FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	//FirstPersonCameraComponent->bUsePawnControlRotation = true;
	
	Arms = CreateDefaultSubobject<USceneComponent>("Arms");
	Arms->SetupAttachment(GetRootComponent());

	//Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	FPArmsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	FPArmsMesh->SetOnlyOwnerSee(true);
	FPArmsMesh->SetupAttachment(Arms);
	FPArmsMesh->bCastDynamicShadow = false;
	FPArmsMesh->CastShadow = false;
	//FPArms->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	//FPArms->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
	
}

void AProjectRebirthCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}

void AProjectRebirthCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	bool test = GetCharacterMovement()->IsFalling();
	float goon = GetWorld()->GetTimeSeconds();

	if (GetCharacterMovement()->IsFalling()) {
		///////////////////////////////////GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::SanitizeFloat(GetWorld()->GetTimeSeconds()));

		
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, test == true ? "Grounded" : "Falling");
	
	//Adds sway to the arms
	//FPArmsMesh->SetRelativeRotation(FMath::RInterpTo(FPArmsMesh->GetRelativeRotation(), FPArmsTargetRot, DeltaTime, 10));
	FPArmsTargetRot = FMath::RInterpTo(FPArmsTargetRot, FRotator(0, -90, 0), DeltaTime, 10);
}

//////////////////////////////////////////////////////////////////////////// Input

void AProjectRebirthCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AProjectRebirthCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AProjectRebirthCharacter::Look);

		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &AProjectRebirthCharacter::Fire);

	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AProjectRebirthCharacter::Fire() {
	GetComponentByClass<UItemHandeler>()->UseItem();

	//UActorComponent * AddComponentByClass
	//(
	//	TSubclassOf< USkeletalMeshComponent > Class,
	//	bool bManualAttachment,
	//	const FTransform & RelativeTransform,
	//	bool bDeferredFinish
	//);
}

void AProjectRebirthCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr && CanMove)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AProjectRebirthCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	float SensitivityCalc = ADS? LookSensitivity * ADSSensitivityPercent: LookSensitivity;

	if (Controller != nullptr && CanLook) {

		//Rotates the arms empty whihc controls the pitch of the camera
		Arms->SetWorldRotation(FRotator(
			FMathf::Clamp(Arms->GetComponentRotation().Pitch - LookAxisVector.Y * SensitivityCalc, -80, 80),
			Arms->GetComponentRotation().Yaw,
			Arms->GetComponentRotation().Roll));

		//Rotates the players control rotation, which is the yaw axis of the camera
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetControlRotation(FRotator(0,GetActorRotation().Yaw + LookAxisVector.X * SensitivityCalc,0));

		//Adds lag to the arms 
		FPArmsTargetRot -= FRotator(0,LookAxisVector.X ,LookAxisVector.Y);
		//FPArmsTargetRot.Yaw = FMath::Clamp(FPArmsTargetRot.Yaw, -140, -40);
		//FPArmsTargetRot.Roll = FMath::Clamp(FPArmsTargetRot.Roll, -5, 3.5);
	}
}

void AProjectRebirthCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool AProjectRebirthCharacter::GetHasRifle()
{
	return bHasRifle;
}
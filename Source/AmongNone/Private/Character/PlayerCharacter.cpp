#include "Character/PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"

APlayerCharacter::APlayerCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(34.0f, 92.5f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->SetRelativeLocation(FVector(0.0f, 0.0f, 65.0f));
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (MoveAction)
		{
			Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		}
		if (LookAction)
		{
			Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		}
		if (LookGamepadAction)
		{
			Input->BindAction(LookGamepadAction, ETriggerEvent::Triggered, this, &APlayerCharacter::LookGamepad);
		}
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	if (!Controller)
	{
		return;
	}

	const FVector2D Axis = Value.Get<FVector2D>().GetClampedToMaxSize(1.0f);
	const FRotator ViewYaw(0.0f, Controller->GetControlRotation().Yaw, 0.0f);
	AddMovementInput(ViewYaw.Vector(), Axis.Y);
	AddMovementInput(FRotationMatrix(ViewYaw).GetUnitAxis(EAxis::Y), Axis.X);
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D Axis = Value.Get<FVector2D>();
	AddControllerYawInput(Axis.X * MouseLookSensitivity);
	AddControllerPitchInput(Axis.Y * MouseLookSensitivity);
}

void APlayerCharacter::LookGamepad(const FInputActionValue& Value)
{
	const FVector2D Axis = Value.Get<FVector2D>();
	const float Scale = GamepadLookRate * GetWorld()->GetDeltaSeconds();
	AddControllerYawInput(Axis.X * Scale);
	AddControllerPitchInput(-Axis.Y * Scale);
}

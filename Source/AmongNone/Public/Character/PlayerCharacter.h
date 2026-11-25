#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class UInputAction;
class USpringArmComponent;
class UInventoryComponent;
struct FInputActionValue;

UCLASS()
class AMONGNONE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> LookGamepadAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> InteractAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (ClampMin = "0"))
	float MouseLookSensitivity = 0.69f;

	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (ClampMin = "0"))
	float GamepadLookRate = 90.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UInventoryComponent> InventoryComponent;
	
	// How far in front of the eyes the interact sweep reaches
	UPROPERTY(EditDefaultsOnly, Category = "Interaction", meta = (ClampMin = "0"))
	float InteractDistance = 200.0f;

	// Radius of the sphere swept along that distance
	UPROPERTY(EditDefaultsOnly, Category = "Interaction", meta = (ClampMin = "0"))
	float InteractRadius = 130.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	bool bDrawInteractDebug = false;

private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void LookGamepad(const FInputActionValue& Value);
	void Interact();
};

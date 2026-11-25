#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class UInputAction;
class USpringArmComponent;
class UHealthComponent;
class UInventoryComponent;
struct FInputActionValue;

UCLASS()
class AMONGNONE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	// // Access gameplay components
	// UFUNCTION(BlueprintPure, Category = "Components")
	// UHealthComponent* GetHealthComponent() const
	// {
	// 	return HealthComponent;
	// }
	//
	// UFUNCTION(BlueprintPure, Category = "Components")
	// UInventoryComponent* GetInventoryComponent() const
	// {
	// 	return InventoryComponent;
	// }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> FollowCamera;
	
	// // Gameplay components
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	// TObjectPtr<UHealthComponent> HealthComponent;
	//
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	// TObjectPtr<UInventoryComponent> InventoryComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> LookGamepadAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (ClampMin = "0"))
	float MouseLookSensitivity = 0.69f;

	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (ClampMin = "0"))
	float GamepadLookRate = 90.0f;

private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void LookGamepad(const FInputActionValue& Value);
};

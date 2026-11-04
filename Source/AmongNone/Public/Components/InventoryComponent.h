// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


class UItemDataAsset;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AMONGNONE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	int32 Capacity = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<TObjectPtr<UItemDataAsset>> Items;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryUpdated OnInventoryUpdated;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(UItemDataAsset* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItem(UItemDataAsset* Item);

	UFUNCTION(BlueprintPure, Category = "Inventory")
	int32 GetQuantity(UItemDataAsset* TargetItem) const;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	TArray<UItemDataAsset*> GetItems() const { return Items; };
};

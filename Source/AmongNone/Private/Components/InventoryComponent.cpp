// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"

#include "Data/ItemDataAsset.h"
#include "Engine/Engine.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventoryComponent::AddItem(UItemDataAsset* Item)
{
	if (!Item)
	{
		return false;
	}
	
	if (Items.Num() >= Capacity)
	{
		UE_LOG(LogTemp, Warning, TEXT("Inventory is full! Cannot add %s"), *Item->GetName());
		return false;
	}
	
	// Check whether this is a new item type
	if (!Items.Contains(Item))
	{
		// Reject new item types of all four slots occupied
		if (GetUniqueItems().Num() >= MaxUniqueItemTypes)
		{
			UE_LOG(LogTemp, Warning, TEXT("Inventory has no available slots!"))
			return false;
		}
	}
	
	Items.Add(Item);
	UE_LOG(LogTemp, Warning, TEXT("Inventory updated"));
	
	if (GEngine)
	{
		FString DebugMessage = FString::Printf(TEXT("Found %s"), *Item->ItemData.DisplayName.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, DebugMessage);
	}
	
	OnInventoryUpdated.Broadcast();
	
	return true;
}

bool UInventoryComponent::RemoveItem(UItemDataAsset* Item)
{
	if (!Item)
	{
		return false;
	}
	
	const int32 RemovedCount = Items.RemoveSingle(Item);
	
	if (RemovedCount > 0)
	{
		OnInventoryUpdated.Broadcast();
		return true;
	}
	
	return false;
}

int32 UInventoryComponent::GetQuantity(UItemDataAsset* TargetItem) const
{
	if (!TargetItem)
	{
		return 0;
	}
	
	int32 TotalCount = 0;
	
	for (const UItemDataAsset* Item : Items)
	{
		if (Item == TargetItem)
		{
			TotalCount++;
		}
	}
	
	return TotalCount;
}

TArray<UItemDataAsset*> UInventoryComponent::GetItems() const
{
	TArray<UItemDataAsset*> Result;
	
	for (UItemDataAsset* Item : Items)
	{
		Result.Add(Item);
	}
	
	return Result;
}

TArray<UItemDataAsset*> UInventoryComponent::GetUniqueItems() const
{
	TArray<UItemDataAsset*> UniqueItems;
	
	for (UItemDataAsset* Item : Items)
	{
		if (Item && !UniqueItems.Contains(Item))
		{
			UniqueItems.Add(Item);
		}
	}
	
	return UniqueItems;
}


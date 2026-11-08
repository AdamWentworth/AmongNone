// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDataAsset.generated.h"

/**
 * 
 */

class UTexture2D;

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Relic UMETA(DisplayName = "Relic"),
	Potion UMETA(DisplayName = "Potion"),
	Wrench UMETA(DisplayName = "Wrench"),
	CoolantCanister UMETA(DisplayName = "CoolantCanister"),
	PowerRegulator UMETA(DisplayName = "PowerRegulator"),
	FuelLineConnector UMETA(DisplayName = "FuelLineConnector"),
	Trap UMETA(DisplayName = "Trap"),
};

USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DisplayName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType ItemType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)	
	float RestoreAmount = 0.0f;
};

UCLASS()
class AMONGNONE_API UItemDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FItemData ItemData;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "Shrine.generated.h"

class UItemDataAsset;
class UPointLightComponent;

UCLASS()
class AMONGNONE_API AShrine : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AShrine();
	
	void Activate();

	bool bIsActive = false;
	
	bool bIsPowered = false;
	
	bool bIsRepaired = false;

	virtual void Interact(AActor* Interactor, UPrimitiveComponent* HitComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UPointLightComponent> ShrineLight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shrine Requirements")
	TObjectPtr<UItemDataAsset> RequiredRelic;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

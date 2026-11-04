// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/Shrine.h"

#include "Components/InventoryComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"


// Sets default values
AShrine::AShrine()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	ShrineLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("ShrineLight"));
	ShrineLight->SetupAttachment(RootComponent);

	ShrineLight->SetVisibility(false);
	bIsActive = false;
}

void AShrine::Activate()
{
	bIsActive = !bIsActive;
	
	ShrineLight->SetVisibility(bIsActive);
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.00f, FColor::Green, TEXT("Shrine Activated"));
	}
	
}

void AShrine::Interact(AActor* Interactor, UPrimitiveComponent* HitComponent)
{
	if (bIsActive || !Interactor)
	{
		return;
	}
	
	UInventoryComponent* InvComp = Interactor->FindComponentByClass<UInventoryComponent>();
	if (!InvComp)
	{
		return;
	}
	if (RequiredRelic && InvComp->GetItems().Contains(RequiredRelic))
	{
		InvComp->RemoveItem(RequiredRelic);
		Activate();
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.00f, FColor::Red, TEXT("Missing relic"));
		}
	}
}

// Called when the game starts or when spawned
void AShrine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShrine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


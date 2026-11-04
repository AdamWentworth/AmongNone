// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/Crate.h"

#include "Components/InventoryComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"

// Sets default values
ACrate::ACrate()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	Lid = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Lid"));
	Lid->SetupAttachment(RootComponent);
}

void ACrate::Open()
{
	if (Lid)
	{
		Lid->Play(false);
	}
}

void ACrate::Interact(AActor* Interactor, UPrimitiveComponent* HitComponent)
{
	Open();
	
	
	if (UInventoryComponent* PlayerInv = Interactor->FindComponentByClass<UInventoryComponent>())
	{
		UE_LOG(LogTemp, Warning, TEXT("Add potion from crate"));
		PlayerInv->AddItem(PotionItem);
		
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Got Potion"));
		}
	}
}

// Called when the game starts or when spawned
void ACrate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACrate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


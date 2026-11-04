// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/EscapePod.h"


// Sets default values
AEscapePod::AEscapePod()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AEscapePod::Interact(AActor* Interactor, UPrimitiveComponent* HitComponent)
{
}

// Called when the game starts or when spawned
void AEscapePod::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEscapePod::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


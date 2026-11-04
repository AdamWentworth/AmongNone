// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/Switch.h"


// Sets default values
ASwitch::ASwitch()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ASwitch::Interact(AActor* Interactor, UPrimitiveComponent* HitComponent)
{
}

// Called when the game starts or when spawned
void ASwitch::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


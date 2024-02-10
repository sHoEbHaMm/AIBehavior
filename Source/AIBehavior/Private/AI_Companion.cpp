// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Companion.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AAI_Companion::AAI_Companion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	RootComponent = staticMesh;
}

// Called when the game starts or when spawned
void AAI_Companion::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAI_Companion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


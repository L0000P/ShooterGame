// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "ShipController.h"
#include "SpaceShooterGameMode.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyController::AEnemyController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Get RootBox of BP
	RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));

}

// Called when the game starts or when spawned
void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Move Enemy
	FVector NewLocation = GetActorLocation();
	NewLocation.X += Speed * DeltaTime;
	SetActorLocation(NewLocation);

	//Destroy Enemy
	if (NewLocation.X < 5.0f)
	{
		this->Destroy();
	}
}

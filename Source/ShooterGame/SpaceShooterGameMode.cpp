// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShooterGameMode.h"
#include "ShooterGame.h"
#include "EnemyController.h"
#include "GameWidget.h"

ASpaceShooterGameMode::ASpaceShooterGameMode() {
	PrimaryActorTick.bCanEverTick = true;
}
void ASpaceShooterGameMode::BeginPlay()
{
	Super::BeginPlay();

	ChangeMenuWidget(StartingWidgetClass);
	((UGameWidget*)CurrentWidget)->Load();
}

void ASpaceShooterGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GameTimer += DeltaTime;
	EnemyTimer -= DeltaTime;

	if (EnemyTimer <= 0.0f)
	{
		float difficultyPercentage = FMath::Min(GameTimer / TIME_TO_MINIMUM_INTERVAL, 1.0f);
		EnemyTimer = MAXIMUM_INTERVAL - (MAXIMUM_INTERVAL - MINIMUM_INTERVAL) * difficultyPercentage;

		if (GetWorld())
		{
			FVector location = FVector(127.0f, FMath::RandRange(-125.0f, 125.0f), 41.60f);
			GetWorld()->SpawnActor<AEnemyController>(EnemyBlueprint, location, FRotator::ZeroRotator);
		}
	}
}

void ASpaceShooterGameMode::IncrementScore()
{
	Score += 100;
	((UGameWidget*)CurrentWidget)->SetScore(Score);
}

void ASpaceShooterGameMode::OnGameOver()
{
	((UGameWidget*)CurrentWidget)->OnGameOver(Score);
}

void ASpaceShooterGameMode::ChangeMenuWidget(TSubclassOf<class UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr) 
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}

	if (NewWidgetClass != nullptr) {
		
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		
		if (CurrentWidget != nullptr) 
		{
			CurrentWidget->AddToViewport();
		}
	}
}

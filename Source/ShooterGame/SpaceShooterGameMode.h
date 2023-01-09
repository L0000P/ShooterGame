// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/GameModeBase.h"
#include "SpaceShooterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API ASpaceShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()

		float MINIMUM_INTERVAL = 0.5f;
		float MAXIMUM_INTERVAL = 2.0f;
		float TIME_TO_MINIMUM_INTERVAL = 30.0f;

	public:
		
		ASpaceShooterGameMode();
		
		virtual void BeginPlay() override;

		
		virtual void Tick(float DeltaSeconds) override;

		void IncrementScore();
		void OnGameOver();

		UPROPERTY(EditAnywhere, Category = "Spawning")
			TSubclassOf<class AEnemyController> EnemyBlueprint;

		float EnemyTimer;
		float GameTimer;

		UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	protected:
		int Score = 0;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> StartingWidgetClass;

		UPROPERTY()
		UUserWidget* CurrentWidget;
};
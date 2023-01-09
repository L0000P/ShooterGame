// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RunTime/UMG/Public/UMG.h"
#include "RunTime/UMG/Public/UMGStyle.h"
#include "RunTime/UMG/Public/Slate/SObjectWidget.h"
#include "RunTime/UMG/Public/IUMGModule.h"
#include "RunTime/UMG/Public/Blueprint/UserWidget.h"
#include "Blueprint/UserWidget.h"
#include "GameWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API UGameWidget : public UUserWidget
{
	GENERATED_BODY()

	public:
		void Load();

		void SetScore(int score);
		void OnGameOver(int score);

		UPROPERTY()
		UTextBlock* ScoreText;
	
};

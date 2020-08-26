// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelOverMenu.generated.h"

/**
 * 
 */
UCLASS()
class HEXAGON_API ULevelOverMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
		class UButton* btnReplay;

	UPROPERTY(meta = (BindWidget))
		class UButton* btnNextLevel;

	UFUNCTION()
	void ReplayLevel();

	UFUNCTION()
	void NextLevel();

	void TearDown();	

	UFUNCTION(BluePrintCallable)
		void Setup(FString nextLevels);

	FString NextLevelName;
};

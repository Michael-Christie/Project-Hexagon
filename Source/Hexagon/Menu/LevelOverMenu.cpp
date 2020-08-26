// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelOverMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

bool ULevelOverMenu::Initialize()
{
	bool b_Success = Super::Initialize();

	if (!b_Success) return false;

	if (btnReplay == nullptr) return false;
	btnReplay->OnClicked.AddDynamic(this, &ULevelOverMenu::ReplayLevel);

	if (btnNextLevel == nullptr) return false;
	btnNextLevel->OnClicked.AddDynamic(this, &ULevelOverMenu::NextLevel);

	return true;
}

void ULevelOverMenu::ReplayLevel()
{
	UE_LOG(LogTemp, Warning, TEXT("Replay Level"));

	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);

	TearDown();
}

void ULevelOverMenu::NextLevel()
{
	UE_LOG(LogTemp, Warning, TEXT("Next Level"));

	if(!NextLevelName.IsEmpty())
		UGameplayStatics::OpenLevel(this, FName(*NextLevelName), false);

	TearDown();
}

void ULevelOverMenu::TearDown()
{
	this->RemoveFromViewport();

	APlayerController*  PC = GetWorld()->GetFirstPlayerController();

	if (PC != nullptr) {
		FInputModeGameOnly InputMode;

		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = false;
	}
}

void ULevelOverMenu::Setup(FString nextLevels)
{
	NextLevelName = nextLevels;
}

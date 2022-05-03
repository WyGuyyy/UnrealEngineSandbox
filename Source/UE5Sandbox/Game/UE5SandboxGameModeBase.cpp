// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5SandboxGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "UE5Sandbox/Targets/UE5SandboxTargetBase.h"
#include "Blueprint/UserWidget.h"
#include "UE5SandboxWidget.h"

void AUE5SandboxGameModeBase::BeginPlay()
{
	TArray<AActor*> Items;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUE5SandboxTargetBase::StaticClass(), Items);
	ItemsInLevel = Items.Num();

	if (GameWidgetClass) {
		
		GameWidget = Cast<UUE5SandboxWidget>(CreateWidget(GetWorld(), GameWidgetClass));

		if (GameWidget) {
			GameWidget->AddToViewport();
			UpdateItemText();
		}
	}
}

void AUE5SandboxGameModeBase::UpdateItemText() 
{
	GameWidget->SetItemText(ItemsCollected, ItemsInLevel);
}

void AUE5SandboxGameModeBase::ItemCollected()
{
	ItemsCollected++;
	UpdateItemText();
}


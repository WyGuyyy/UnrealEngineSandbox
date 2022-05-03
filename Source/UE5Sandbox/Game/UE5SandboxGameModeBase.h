// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UE5SandboxGameModeBase.generated.h"

class UUE5SandboxWidget;

/**
 * 
 */
UCLASS()
class UE5SANDBOX_API AUE5SandboxGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:

	int32 ItemsCollected = 0;
	int32 ItemsInLevel = 0;

	//TODO - Implment Widget Variables
	UPROPERTY(EditAnywhere, Category="Widgets")
		TSubclassOf<class UUserWidget> GameWidgetClass;

	UPROPERTY()
		UUE5SandboxWidget* GameWidget;


	virtual void BeginPlay() override;

	void UpdateItemText();

public:

	void ItemCollected();
	
};

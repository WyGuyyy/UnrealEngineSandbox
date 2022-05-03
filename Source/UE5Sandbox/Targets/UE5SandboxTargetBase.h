// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UE5SandboxTargetBase.generated.h"

// class UMaterialInstanceDynamic;

UCLASS()
class UE5SANDBOX_API AUE5SandboxTargetBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUE5SandboxTargetBase();

	// Define Components
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	int32 direction = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float initialLocation = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float movementScale = 1000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float speed = 1000;

	bool isHit = false;

	UFUNCTION()
	void OnTargetHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintNativeEvent)
		void Collected();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void ChangeDirection();

private:
	UMaterialInstanceDynamic* DynamicMaterial;

};

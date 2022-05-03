// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5SandboxItemBase.h"
#include "UE5Sandbox/Game/UE5SandboxPlayer.h"
#include "UE5Sandbox/Game/UE5SandboxGameModeBase.h"

// Sets default values
AUE5SandboxItemBase::AUE5SandboxItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Components - Before this step they won't exist on our Actor, they've only been defined.
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AUE5SandboxItemBase::OverlapBegin);

}

// Called when the game starts or when spawned
void AUE5SandboxItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AUE5SandboxItemBase::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (Cast<AUE5SandboxPlayer>(OtherActor) != nullptr) {
		
		Collected();

	}

}

void AUE5SandboxItemBase::Collected_Implementation()
{
	
	AUE5SandboxGameModeBase* GameMode = Cast<AUE5SandboxGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode) {
		GameMode->ItemCollected();
	}

}

// Called every frame
void AUE5SandboxItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5Sandbox/Targets/UE5SandboxTargetBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
#include <UE5Sandbox/Game/UE5SandboxPlayer.h>
#include "UE5Sandbox/Game/UE5SandboxGameModeBase.h"

// Sets default values
AUE5SandboxTargetBase::AUE5SandboxTargetBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Test"));
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void AUE5SandboxTargetBase::BeginPlay()
{
	Super::BeginPlay();
	initialLocation = Mesh->GetComponentLocation().Y;
	Mesh->OnComponentHit.AddDynamic(this, &AUE5SandboxTargetBase::OnTargetHit);
	auto Material = Mesh->GetMaterial(0);

	DynamicMaterial = UMaterialInstanceDynamic::Create(Material, NULL);
	Mesh->SetMaterial(0, DynamicMaterial);
	// ChangeDirection();
	
}

// Called every frame
void AUE5SandboxTargetBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector relativeLocation = Mesh->GetComponentLocation();
	if (relativeLocation.Y > initialLocation + movementScale) {
		direction = 1;
	}
	else if (relativeLocation.Y < initialLocation - movementScale) {
		direction = 0;
	}

	relativeLocation.Y = relativeLocation.Y + (direction == 0 ? DeltaTime * speed : DeltaTime * -(speed));
	Mesh->SetWorldLocation(relativeLocation);
}

// Next time start markup file - Document everything!!!
// also look up dynamic material and material interface classes
void AUE5SandboxTargetBase::OnTargetHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	DynamicMaterial->SetVectorParameterValue(TEXT("GlowColor"), FLinearColor::Green);
	Mesh->SetMaterial(0, DynamicMaterial);

	if (Cast<APawn>(OtherActor) != nullptr) {
		
		Collected();

	}
}

void AUE5SandboxTargetBase::Collected_Implementation()
{

	AUE5SandboxGameModeBase* GameMode = Cast<AUE5SandboxGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode && !isHit) {
		GameMode->ItemCollected();
		isHit = true;
	}

}

void AUE5SandboxTargetBase::ChangeDirection()
{

	//FVector relativeLocation = GetTransform().InverseTransformPosition(Mesh->GetComponentLocation());
	FVector relativeLocation = Mesh->GetComponentLocation();
	relativeLocation.Y = relativeLocation.Y + (direction == 0 ? 1000 : -1000);

	direction = (direction == 0 ? 1 : 0);

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = FName("ChangeDirection");
	LatentInfo.Linkage = 0;
	LatentInfo.UUID = 0;

	UKismetSystemLibrary::MoveComponentTo(Mesh, relativeLocation, Mesh->GetComponentRotation(), true, true, 2.0f, true, EMoveComponentAction::Move, LatentInfo);
}


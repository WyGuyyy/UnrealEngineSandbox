// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5SandboxPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AUE5SandboxPlayer::AUE5SandboxPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Components - Before this step they wont exist on our Actor, they've only been defined
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	// Set the Root Component to be our Mesh
	RootComponent = Mesh;
	// Attach the SpringArm to the Mesh, Spring will now follow the Mesh transform
	SpringArm->SetupAttachment(Mesh);
	// Attach the Camera to the SpringArm, Camera will now follow the SpringArm transform
	Camera->SetupAttachment(SpringArm);

	//Set physics to True
	Mesh->SetSimulatePhysics(true);

	Mesh->OnComponentHit.AddDynamic(this, &AUE5SandboxPlayer::OnHit);

}

// Called when the game starts or when spawned
void AUE5SandboxPlayer::BeginPlay()
{
	Super::BeginPlay();
	//Account for mass in MoveForce
	MoveForce *= Mesh->GetMass();
	JumpImpulse *= Mesh->GetMass();
	
}

// Called every frame
void AUE5SandboxPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUE5SandboxPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Custom Input Axis Bindings
	InputComponent->BindAxis("MoveForward", this, &AUE5SandboxPlayer::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AUE5SandboxPlayer::MoveRight);

	//Custom Action Binding
	InputComponent->BindAction("Jump", IE_Pressed, this, &AUE5SandboxPlayer::Jump);

}

void AUE5SandboxPlayer::MoveRight(float Value)
{
	// Get The Right vector of the camera as it doesn't rotate and move the player in this direction based on the input and MoveForce
	const FVector Right = Camera->GetRightVector() * MoveForce * Value;
	Mesh->AddForce(Right);
}

void AUE5SandboxPlayer::MoveForward(float Value)
{
	// Get The Forward vector of the camera as it doesn't rotate and move the player in this direction based on the input and MoveForce
	const FVector Forward = Camera->GetForwardVector() * MoveForce * Value;
	Mesh->AddForce(Forward);
}

void AUE5SandboxPlayer::Jump()
{
	// Cap the number of jumps we can make
	if (JumpCount >= MaxJumpCount) { return; }

	// Apply an impulse to the Mesh in the Z Axis
	Mesh->AddImpulse(FVector(0, 0, JumpImpulse));

	//Track how many times we've jumped
	JumpCount++;
}

void AUE5SandboxPlayer::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) 
{
	//Get Direction
	const float HitDirection = Hit.Normal.Z;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("Z Normal %f"), HitDirection));

	//If its more than 0 then we've hit something below us. 1 is flat, anything between is a slope
	if (HitDirection > 0) {
		JumpCount = 0;
	}
}


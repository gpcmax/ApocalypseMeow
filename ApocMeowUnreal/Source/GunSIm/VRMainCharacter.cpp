// Fill out your copyright notice in the Description page of Project Settings.

#include "VRMainCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "MotionControllerComponent.h"
#include "Components/BoxComponent.h"
#include "Engine.h"
#include "HitProxies.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AVRMainCharacter::AVRMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//sets player height for vr
	GetCapsuleComponent()->InitCapsuleSize(20.f, 20.f);

	//set up camera
	VROrigin = CreateDefaultSubobject<USceneComponent>(TEXT("VROrigin"));
	VROrigin->SetupAttachment(RootComponent);

	VRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("VrCamera"));
	VRCamera->SetupAttachment(VROrigin);

	//******************set up motion controller Support
	LeftMC = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftMC"));
	LeftMC->SetupAttachment(RootComponent);

	LeftHandMeshSK = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftHandMesh"));
	LeftHandMeshSK->SetupAttachment(LeftMC);

	LeftHandCol = CreateDefaultSubobject<USphereComponent>(TEXT("LeftHandCol"));
	LeftHandCol->SetupAttachment(LeftHandMeshSK);

	RightMC = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightMC"));
	RightMC->SetupAttachment(RootComponent);

	RightHandMeshSK = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightHandMesh"));
	RightHandMeshSK->SetupAttachment(RightMC);

	RightHandCol = CreateDefaultSubobject<USphereComponent>(TEXT("RightHandCol"));
	RightHandCol->SetupAttachment(RightHandMeshSK);

	//************ bodycomponents
	PistolInHand = CreateDefaultSubobject<USceneComponent>(TEXT("PistolInHand"));
	PistolInHand->SetupAttachment(RightHandMeshSK);

	VRBodyScene = CreateDefaultSubobject<USceneComponent>(TEXT("VRBodyScene"));
	VRBodyScene->SetupAttachment(RootComponent);

	VRBodyCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("VRBodyCap"));
	VRBodyCapsule->SetupAttachment(VRBodyScene);

	AmmoPouch = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AmmoPouch"));
	AmmoPouch->SetupAttachment(VRBodyCapsule);

	AmmoPouchCol = CreateDefaultSubobject<UBoxComponent>(TEXT("AmmoPouchCol"));
	AmmoPouchCol->SetupAttachment(AmmoPouch);

}

// Called when the game starts or when spawned
void AVRMainCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AVRMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVRMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AVRMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AVRMainCharacter::MoveRight);
}

//handles player movement based off the left trackpad
void AVRMainCharacter::MoveForward(float Value)
{
	const FVector Direction = VRCamera->GetForwardVector();
	AddMovementInput(Direction, Value);
}

//handles player movement based off the left trackpad
void AVRMainCharacter::MoveRight(float Value)
{
	const FVector Direction = VRCamera->GetRightVector();
	AddMovementInput(Direction, Value);
}

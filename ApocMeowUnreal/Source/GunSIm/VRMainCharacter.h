// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VRMainCharacter.generated.h"

UCLASS()
class GUNSIM_API AVRMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVRMainCharacter();

	//vr camera
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		class UCameraComponent* VRCamera;

	//*********************************controllers
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MotionController)
		class UMotionControllerComponent* RightMC;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Hand)
		USkeletalMeshComponent* RightHandMeshSK;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = HandCol)
		class USphereComponent* RightHandCol;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MotionController)
		class UMotionControllerComponent* LeftMC;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Hand)
		USkeletalMeshComponent* LeftHandMeshSK;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = HandCol)
		class USphereComponent* LeftHandCol;

	//********************************VR Body 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Body)
		USceneComponent* VRBodyScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Body)
		UCapsuleComponent* VRBodyCapsule;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Body)
		//USkeletalMeshComponent* Holster;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Body)
		//class UBoxComponent* HolsterCol;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Body)
	//	class USkeletalMeshComponent* PistolMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Hand)
		USceneComponent* PistolInHand;

	UPROPERTY(EditDefaultsOnly, blueprintReadWrite, Category = Body)
		USceneComponent* VROrigin;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Body)
		//USceneComponent* PistolInHolsterLoc;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Body)
		UStaticMeshComponent* AmmoPouch;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Body)
		class UBoxComponent* AmmoPouchCol;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Body)
	//	USkeletalMeshComponent* AmmoMag4Pistol;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Hand)
		float Scrap;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void MoveForward(float Value);

	void MoveRight(float Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};

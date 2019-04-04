// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AI_Character.generated.h"

UCLASS()
class GUNSIM_API AAI_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAI_Character();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Health)
		float MaxHealth;
	/*
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = HitBox)
		class UCapsuleComponent HeadShot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = HitBox)
		class UCapsuleComponent BodyShot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = HitBox)
		class UCapsuleComponent LeftLimbShot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = HitBox)
		class UCapsuleComponent RightLimbShot;
		*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Health)
		float CurrentHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Health)
		float MaxArmorHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Health)
		float CurrentArmorHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Ragdoll)
		bool bRagDoll;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Clothes)
		USkeletalMeshComponent* ShirtMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Clothes)
		USkeletalMeshComponent* PantsMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Clothes)
		USkeletalMeshComponent* BeltMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Clothes)
		USkeletalMeshComponent* BootsMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Health)
		bool bIArmored;

	UPROPERTY(EditDefaultsOnly, Category = Audio)
		class USoundCue* EnemyHit;

	UPROPERTY(EditDefaultsOnly, Category = Audio)
		class USoundCue* HitMarker;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Hand)
		//float Scrap;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintCallable)
		void HurtAi(float GunDam, bool bIsShark);

	UFUNCTION(BlueprintCallable)
		void KillEnemies();
	
	UFUNCTION(BlueprintCallable)
		void RagdollEnemy();
	
};

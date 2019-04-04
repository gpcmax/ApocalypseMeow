// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PistolWeaponsMaster.generated.h"

UCLASS()
class GUNSIM_API APistolWeaponsMaster : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APistolWeaponsMaster();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
		USceneComponent* PistolZeroPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
		class USkeletalMeshComponent* PistolMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
		USceneComponent* MagLoc;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
		USceneComponent* Muzzle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
		class UBoxComponent* WeaponGrabCol;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
		class UBoxComponent* AmmoBoxCol;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
		class UTextRenderComponent* AmmoCounterForPistol;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon)
		int MaxPistolAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon)
		int CurrentPistolAmmo;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable , Category = Weapon)
	void FirePistol();

	UFUNCTION(BlueprintCallable, Category = Weapon)
		void FireProjectilePistol();

	void GrabPistol();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//class to spawn projectile
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
		TSubclassOf<class AProjectileMaster> ProjectileClass;
	
	
};

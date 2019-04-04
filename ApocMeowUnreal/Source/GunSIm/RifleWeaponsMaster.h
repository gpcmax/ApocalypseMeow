//  actor meant to set up the base functinos of the vr rifle
//  artist are able then to edit components of the child and change the mesh for the weapon
//  artist are able to quickly make multiple different weapons very quickly

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RifleWeaponsMaster.generated.h"

UCLASS()
class GUNSIM_API ARifleWeaponsMaster : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARifleWeaponsMaster();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
		USceneComponent* RifleZeroPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
		class USkeletalMeshComponent* RifleMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
		USceneComponent* MagLoc;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
		USceneComponent* Muzzle;

	UPROPERTY(EditDefaultsOnly, Category = Audio)
		class USoundCue* FireBulletSound;

	UPROPERTY(EditDefaultsOnly, Category = Audio)
		class USoundCue* FireNoBulletSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
		class USphereComponent* SecondHandCol;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
		class UTextRenderComponent* AmmoCounterForRifle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
		class UBoxComponent* RifleBoxCol;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon)
		int MaxRifleAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon)
		int CurrentRifleAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Hand)
		float Scrap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Bullet)
		float SkewAmount;

	/*ShotGun spread code*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Bullet)
		float ShotGunSkew01;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Bullet)
		float ShotGunSkew02;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Bullet)
		float ShotGunSkew03;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Bullet)
		float ShotGunSkew04;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Bullet)
		float ShotGunSkew05;
	/*end of shotgun spread code*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Bullet)
		float RayCastBulletDamage;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AProjectileMaster> ProjectileClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = Weapon)
		void FireRifle();

	UFUNCTION(BlueprintCallable, Category = Weapon)
		void FireProjectile();

	UFUNCTION(BlueprintCallable, Category = Weapon)
		void FireSpreadShot(USceneComponent* Muzzle01, USceneComponent* Muzzle02, USceneComponent* Muzzle03, USceneComponent* Muzzle04, USceneComponent* Muzzle05);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};

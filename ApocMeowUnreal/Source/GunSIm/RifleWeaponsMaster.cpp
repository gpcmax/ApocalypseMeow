// Fill out your copyright notice in the Description page of Project Settings.
//Apocalypse Meow
//Sleepless Ambitions
///2018
//Gage Copelin
//  actor meant to set up the base functinos of the vr rifle
//  artist are able then to edit components of the child and change the mesh for the weapon
//  artist are able to quickly make multiple different weapons very quickly

#include "RifleWeaponsMaster.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine.h"
#include "HitProxies.h"
#include "VRMainCharacter.h"
#include "ProjectileMaster.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "AI_Character.h"

// Sets default values
ARifleWeaponsMaster::ARifleWeaponsMaster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RifleZeroPoint = CreateDefaultSubobject<USceneComponent>(TEXT("RifleZeroPoint"));
	RootComponent = RifleZeroPoint;

	RifleMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RifleMesh"));
	RifleMesh->SetupAttachment(RootComponent);

	MagLoc = CreateDefaultSubobject<USceneComponent>(TEXT("MagLoc"));
	MagLoc->SetupAttachment(RifleMesh);

	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(RifleMesh);

	SecondHandCol = CreateDefaultSubobject<USphereComponent>(TEXT("SecondHandCol"));
	SecondHandCol->SetupAttachment(RifleMesh);

	AmmoCounterForRifle = CreateDefaultSubobject<UTextRenderComponent>(TEXT("AmmoCounterForRifle"));
	AmmoCounterForRifle->SetupAttachment(RifleMesh);

	RifleBoxCol = CreateDefaultSubobject<UBoxComponent>(TEXT("RifleBoxCol"));
	RifleBoxCol->SetupAttachment(RifleMesh);

}

// Called when the game starts or when spawned
void ARifleWeaponsMaster::BeginPlay()
{
	Super::BeginPlay();
	
	//sets max rifle ammo
	//MaxRifleAmmo = 30;
	//sets starting ammo for rifle
	CurrentRifleAmmo = 0;
}

//this function handles raycasting if the gun is supposed to be a raycasted gun
//in editor can be chosen by art team 
void ARifleWeaponsMaster::FireRifle()
{
	FHitResult* HitResult = new FHitResult();
	FVector StartTrace = Muzzle->GetComponentLocation();
	FVector ForwardVector = Muzzle->GetForwardVector();
	FVector EndTrace = ((ForwardVector * 5000.f) + StartTrace);
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams();

	if (CurrentRifleAmmo > 0)
	{
		//ticks one ammo down every shot
		CurrentRifleAmmo = CurrentRifleAmmo - 1;
		//checks if it hits something
		if (GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, EndTrace, ECC_Camera, *TraceParams))
		{
			//if it hits something it goes through
			AAI_Character* AI_Character = Cast<AAI_Character>(HitResult->GetActor());
			//checks if it hits ai
			if (AI_Character != NULL)
			{
				//if it does call function on ai and perfrom it
				AI_Character->HurtAi(RayCastBulletDamage,false);
				Scrap = Scrap + 100.f;
			}
			//DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(255, 0, 0), true, 5.f);
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("You hit: %s"), *HitResult->Actor->GetName()));
		}
	}
}

//this handles projectiles if the current weapon was to be a projectile based gun
//in editor can be chosen by art team 
void ARifleWeaponsMaster::FireProjectile()
{
	FVector MuzzleLoc = Muzzle->GetComponentLocation();
	FRotator MuzzleRot = Muzzle->GetComponentRotation();
	UWorld* World = GetWorld();

	if (CurrentRifleAmmo > 0)
	{
		
		if (ProjectileClass)
		{
			FVector MuzzleLoc = Muzzle->GetComponentLocation();
			FRotator MuzzleRot = Muzzle->GetComponentRotation();
			UWorld* World = GetWorld();
			//skew aim slightly upward
			//can be edited in the editor
			MuzzleRot.Pitch += SkewAmount;
			if (World)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.Instigator = Instigator;
				//Spawn the projectile at the muzzle
				AProjectileMaster* Projectile = World->SpawnActor<AProjectileMaster>(ProjectileClass, MuzzleLoc, MuzzleRot, SpawnParams);
				if (Projectile)
				{
					//set projectile's initial trajectory
					FVector LaunchDirection = MuzzleRot.Vector();
					Projectile->FireInDirection(LaunchDirection);
					UGameplayStatics::PlaySoundAtLocation(World, FireBulletSound, MuzzleLoc);
					CurrentRifleAmmo = CurrentRifleAmmo - 1;
				}
			}
		}
	}
	else
	{
		UGameplayStatics::PlaySoundAtLocation(World, FireNoBulletSound, MuzzleLoc);
	}
}

void ARifleWeaponsMaster::FireSpreadShot(USceneComponent * Muzzle01, USceneComponent * Muzzle02, USceneComponent * Muzzle03, USceneComponent * Muzzle04, USceneComponent * Muzzle05)
{
	/* for when a weapon needs multiple muzzles and can fire a spread like a shotgun*/
	//base muzzle
	FVector MuzzleLoc = Muzzle->GetComponentLocation();
	FRotator MuzzleRot = Muzzle->GetComponentRotation();
	FVector MuzzleLoc01 = Muzzle01->GetComponentLocation();
	FRotator MuzzleRot01 = Muzzle01->GetComponentRotation();
	FVector MuzzleLoc02 = Muzzle02->GetComponentLocation();
	FRotator MuzzleRot02 = Muzzle02->GetComponentRotation();
	FVector MuzzleLoc03 = Muzzle03->GetComponentLocation();
	FRotator MuzzleRot03 = Muzzle03->GetComponentRotation();
	FVector MuzzleLoc04 = Muzzle04->GetComponentLocation();
	FRotator MuzzleRot04 = Muzzle04->GetComponentRotation();
	FVector MuzzleLoc05 = Muzzle05->GetComponentLocation();
	FRotator MuzzleRot05 = Muzzle05->GetComponentRotation();

	UWorld* World = GetWorld();

	if (CurrentRifleAmmo > 0)
	{

		if (ProjectileClass)
		{
			FVector MuzzleLoc = Muzzle->GetComponentLocation();
			FRotator MuzzleRot = Muzzle->GetComponentRotation();
			UWorld* World = GetWorld();
			//skew aim slightly upward
			//can be edited in the editor
			MuzzleRot.Pitch += SkewAmount;
			if (World)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.Instigator = Instigator;
				//Spawn the projectile at the muzzle
				AProjectileMaster* Projectile = World->SpawnActor<AProjectileMaster>(ProjectileClass, MuzzleLoc, MuzzleRot, SpawnParams);
				AProjectileMaster* Projectile1 = World->SpawnActor<AProjectileMaster>(ProjectileClass, MuzzleLoc01, MuzzleRot01, SpawnParams);
				AProjectileMaster* Projectile2 = World->SpawnActor<AProjectileMaster>(ProjectileClass, MuzzleLoc02, MuzzleRot02, SpawnParams);
				AProjectileMaster* Projectile3 = World->SpawnActor<AProjectileMaster>(ProjectileClass, MuzzleLoc03, MuzzleRot03, SpawnParams);
				AProjectileMaster* Projectile4 = World->SpawnActor<AProjectileMaster>(ProjectileClass, MuzzleLoc04, MuzzleRot04, SpawnParams);
				AProjectileMaster* Projectile5 = World->SpawnActor<AProjectileMaster>(ProjectileClass, MuzzleLoc05, MuzzleRot05, SpawnParams);
				
				//checks each projectile from each muzzle and fires in the direction that is specified
				if (Projectile)
				{
					//set projectile's initial trajectory
					FVector LaunchDirection = MuzzleRot.Vector();
					Projectile->FireInDirection(LaunchDirection);
					UGameplayStatics::PlaySoundAtLocation(World, FireBulletSound, MuzzleLoc);
					CurrentRifleAmmo = CurrentRifleAmmo - 1;
				}
				if (Projectile1)
				{
					//set projectile's initial trajectory
					FVector LaunchDirection = MuzzleRot01.Vector();
					Projectile1->FireInDirection(LaunchDirection);
					//UGameplayStatics::PlaySoundAtLocation(World, FireBulletSound, MuzzleLoc);
					//CurrentRifleAmmo = CurrentRifleAmmo - 1;
				}
				if (Projectile2)
				{
					//set projectile's initial trajectory
					FVector LaunchDirection = MuzzleRot02.Vector();
					Projectile2->FireInDirection(LaunchDirection);
					//UGameplayStatics::PlaySoundAtLocation(World, FireBulletSound, MuzzleLoc);
					//CurrentRifleAmmo = CurrentRifleAmmo - 1;
				}
				if (Projectile3)
				{
					//set projectile's initial trajectory
					FVector LaunchDirection = MuzzleRot03.Vector();
					Projectile3->FireInDirection(LaunchDirection);
					//UGameplayStatics::PlaySoundAtLocation(World, FireBulletSound, MuzzleLoc);
					//CurrentRifleAmmo = CurrentRifleAmmo - 1;
				}
				if (Projectile4)
				{
					//set projectile's initial trajectory
					FVector LaunchDirection = MuzzleRot04.Vector();
					Projectile4->FireInDirection(LaunchDirection);
					//UGameplayStatics::PlaySoundAtLocation(World, FireBulletSound, MuzzleLoc);
					//CurrentRifleAmmo = CurrentRifleAmmo - 1;
				}
				if (Projectile5)
				{
					//set projectile's initial trajectory
					FVector LaunchDirection = MuzzleRot05.Vector();
					Projectile5->FireInDirection(LaunchDirection);
					//UGameplayStatics::PlaySoundAtLocation(World, FireBulletSound, MuzzleLoc);
					//CurrentRifleAmmo = CurrentRifleAmmo - 1;
				}
			}
		}
	}
	else
	{
		UGameplayStatics::PlaySoundAtLocation(World, FireNoBulletSound, MuzzleLoc);
	}
}

// Called every frame
void ARifleWeaponsMaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


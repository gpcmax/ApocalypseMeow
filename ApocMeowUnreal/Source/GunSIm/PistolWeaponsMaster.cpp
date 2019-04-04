// Fill out your copyright notice in the Description page of Project Settings.

#include "PistolWeaponsMaster.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine.h"
#include "HitProxies.h"
#include "VRMainCharacter.h"
#include "AI_Character.h"
#include "ProjectileMaster.h"

// Sets default values
APistolWeaponsMaster::APistolWeaponsMaster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PistolZeroPoint = CreateDefaultSubobject<USceneComponent>(TEXT("PistolZeroPoint"));
	RootComponent = PistolZeroPoint;

	PistolMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PistolMesh"));
	PistolMesh->SetupAttachment(RootComponent);

	MagLoc = CreateDefaultSubobject<USceneComponent>(TEXT("MagLoc"));
	MagLoc->SetupAttachment(PistolMesh);

	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(PistolMesh);

	WeaponGrabCol = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponGrabCol"));
	WeaponGrabCol->SetupAttachment(PistolMesh);
	WeaponGrabCol->bGenerateOverlapEvents = true;

	AmmoCounterForPistol = CreateDefaultSubobject<UTextRenderComponent>(TEXT("AmmCounterForPistol"));
	AmmoCounterForPistol->SetupAttachment(PistolMesh);

	AmmoBoxCol = CreateDefaultSubobject<UBoxComponent>(TEXT("AmmoBoxCol"));
	AmmoBoxCol->SetupAttachment(PistolMesh);

	CurrentPistolAmmo = MaxPistolAmmo;


}

// Called when the game starts or when spawned
void APistolWeaponsMaster::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentPistolAmmo = MaxPistolAmmo;
	
}

void APistolWeaponsMaster::FirePistol()
{
	if (CurrentPistolAmmo > 0)
	{
		FHitResult* HitResult = new FHitResult();
		FVector StartTrace = Muzzle->GetComponentLocation();
		FVector ForwardVector = Muzzle->GetForwardVector();
		FVector EndTrace = ((ForwardVector * 5000.f) + StartTrace);
		FCollisionQueryParams* TraceParams = new FCollisionQueryParams();

		//ammo
		CurrentPistolAmmo = CurrentPistolAmmo - 1;
		if (GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, EndTrace, ECC_Visibility, *TraceParams))
		{
			AAI_Character* AI_Character = Cast<AAI_Character>(HitResult->GetActor());
			if (AI_Character != NULL)
			{
				AI_Character->HurtAi(10.f,false);
			}
			DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(255, 0, 0), false, 5.f);
		}
	}
}

void APistolWeaponsMaster::FireProjectilePistol()
{
	if (CurrentPistolAmmo > 0)
	{
		FVector MuzzleLocation = Muzzle->GetComponentLocation();
		FRotator MuzzleRot = Muzzle->GetComponentRotation();
		MuzzleRot.Pitch += 10.0f;
		UWorld* World = GetWorld();
		if (World)
		{
			CurrentPistolAmmo = CurrentPistolAmmo - 1;
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			//spawn projectile at muzzle
			AProjectileMaster* Projectile = World->SpawnActor<AProjectileMaster>(ProjectileClass, MuzzleLocation, MuzzleRot, SpawnParams);
			if (Projectile)
			{
				//set the projectiles initial trajectory
				FVector LaunchDirection = MuzzleRot.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}
}

void APistolWeaponsMaster::GrabPistol()
{
	//USphereComponent* RightHandCollision = Cast<USphereComponent>(AVRMainCharacter::RightHandCol);
			/*
	if (WeaponGrabCol->IsOverlappingComponent()
	{
		AVRMainCharacter* PistolInHand = Cast<AVRMainCharacter>(PistolInHand);
		AttachToActor(PistolInHand, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		//AttachToComponent(PistolInHand, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}*/

}


// Called every frame
void APistolWeaponsMaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//AmmoCounterForPistol->SetText(CurrentPistolAmmo);
}


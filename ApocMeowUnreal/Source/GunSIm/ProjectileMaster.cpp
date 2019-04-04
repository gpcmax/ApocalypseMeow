// Fill out your copyright notice in the Description page of Project Settings.
//Apocalypse Meow
//Sleepless Ambitions
///2018
//Gage Copelin

#include "ProjectileMaster.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Engine.h"
#include "AI_Character.h"

// Sets default values
AProjectileMaster::AProjectileMaster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//use a sphere for collision
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	//CollisionComponent->OnComponentHit.AddDynamic(this, &AProjectileMaster::OnHit);
	//set the spheres collsion radius
	CollisionComponent->InitSphereRadius(15.0f);
	//set the root
	RootComponent = CollisionComponent;

	//sets the mesh that can be edited by the artist
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	BulletMesh->SetupAttachment(RootComponent);

	//projectile Varaibles
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
	ProjectileMovementComp->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComp->InitialSpeed = 3000.f;
	ProjectileMovementComp->MaxSpeed = 3000.f;
	ProjectileMovementComp->bRotationFollowsVelocity = true;
	ProjectileMovementComp->bShouldBounce = true;
	ProjectileMovementComp->Bounciness = 0.3f;

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectileMaster::OnCompOverlap);
	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void AProjectileMaster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectileMaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//function that initializes the projectiles velocity in the shoot direction
void AProjectileMaster::FireInDirection(const FVector & ShootDirection)
{
	ProjectileMovementComp->Velocity = ShootDirection * ProjectileMovementComp->InitialSpeed;
}

void AProjectileMaster::OnCompOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//weapon specific damages are handled in the BP
	AAI_Character* AI_Character = Cast<AAI_Character>(OtherActor);
	if (AI_Character == nullptr)
	{
		return;
	}

	if (AI_Character != NULL)
	{
		//if it hits the enemy it damages it
		AI_Character->HurtAi(BulletDamage, false);
	}
}

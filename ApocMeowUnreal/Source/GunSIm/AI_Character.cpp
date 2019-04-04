//Apocalypse Meow
//Sleepless Ambitions
///2018
//Gage Copelin

#include "AI_Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "VRMainCharacter.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AAI_Character::AAI_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	ShirtMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ShirtMesh"));
	ShirtMesh->SetupAttachment(GetMesh());

	PantsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PantsMesh"));
	PantsMesh->SetupAttachment(GetMesh());

	BeltMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BeltMesh"));
	BeltMesh->SetupAttachment(GetMesh());

	BootsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BootMesh"));
	BootsMesh->SetupAttachment(GetMesh());

	MaxHealth = 50.f;
	
	MaxArmorHealth = 100.f;

	bRagDoll = false;
	//bIArmored = false;
	//Scrap = 0.f;
}

// Called when the game starts or when spawned
void AAI_Character::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentHealth = MaxHealth;
	//CurrentArmorHealth = MaxArmorHealth
}

//function that damages the enemy
void AAI_Character::HurtAi(float GunDam,bool bIsShark)
{
	if (bIsShark)
	{
		/*if is a shark or another damage over time it only plays sound once*/
		CurrentHealth = CurrentHealth - GunDam;
		if (CurrentHealth < 0)
		{
			//main body mesh
			RagdollEnemy();
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			InitialLifeSpan = 2.0f;
			bRagDoll = true;
		}
	}
	else
	{
		/* if a one time damage plays sound everytime*/
		CurrentHealth = CurrentHealth - GunDam;
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), EnemyHit, GetMesh()->GetComponentLocation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitMarker, GetMesh()->GetComponentLocation());
		

		if (CurrentHealth < 0)
		{
			//main body mesh
			RagdollEnemy();
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			InitialLifeSpan = 2.0f;
			bRagDoll = true;
		}
	}
}
/*Destroys the enemy*/
void AAI_Character::KillEnemies()
{
	Destroy();
}

/*Function that is called when enemy dies, has them ragdoll*/
void AAI_Character::RagdollEnemy()
{
	//body
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
}

// Called every frame
void AAI_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
//ai player has no player input
void AAI_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


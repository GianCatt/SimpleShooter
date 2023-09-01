// Fill out your copyright notice in the Description page of Project Settings.


#include "Launcher.h"

#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALauncher::ALauncher()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ALauncher::PullTrigger()
{
	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr) return;

	FVector Location;
	FRotator Rotation;
	FActorSpawnParameters Params;
	
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	
	if (AmmoCount > 0)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, "MuzzleFlashSocket");
		--AmmoCount;
		FVector End = Location + Rotation.Vector() * SpawnOffset;
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, End, Rotation, Params);
		if (Projectile == nullptr) return;
		Projectile->SetOwner(this);
	}
	
}

// Called when the game starts or when spawned
void ALauncher::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALauncher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AController* ALauncher::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return false;
	return OwnerPawn->GetController();
}



// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "InputBehavior.h"
#include "ShooterCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Tasks/Task.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile"));
	SetRootComponent(ProjectileMesh);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->MaxSpeed = 7000.f;
	ProjectileMovementComponent->InitialSpeed = 7000.f;
}


// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
	AActor* MyOwner = GetOwner();

	if(MyOwner == nullptr)
	{
		Destroy();
		UE_LOG(LogTemp, Warning, TEXT("Owner is null"));
		return;
	}

	AController* MyOwnerInstigator = MyOwner->GetInstigatorController();
	UClass* DamageTypeClass = UDamageType::StaticClass();
	TArray<AActor*> IgnoreActors;
	TArray<AActor*> OverlappedActors;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	
	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UE_LOG(LogTemp, Warning, TEXT("Owner is not Null"))
		ExplosionLocation = Hit.Location;
		DrawDebugSphere(GetWorld(), Hit.Location, ExplosionRadius, 10.f, FColor::Red, true, 3.f);
		UKismetSystemLibrary::SphereOverlapActors(GetWorld(), Hit.Location, ExplosionRadius, ObjectTypes, ACharacter::StaticClass(), IgnoreActors, OverlappedActors);
		UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, Hit.Location, ExplosionRadius, DamageTypeClass, IgnoreActors, this, MyOwnerInstigator, true);
		Destroy();

		
		for (AActor* Actor : OverlappedActors)
		{
			ACharacter* Character = Cast<ACharacter>(Actor);
			if (Character != nullptr)
			{
				FVector Direction = Character->GetActorLocation() - ExplosionLocation;
				Direction.Normalize();

				// Optionally modify force based on distance to explosion
				// float ForceMagnitude = FMath::Clamp(ExplosionForce * (1.0f - (Distance / ExplosionRadius)), MinForce, MaxForce);

				FVector LaunchVelocity = Direction * ExplosionForce;
				Character->LaunchCharacter(LaunchVelocity, true, true);
			}
			
		}
	}
	
	
	
}


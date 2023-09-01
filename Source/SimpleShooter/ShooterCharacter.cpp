// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Launcher.h"
#include "Gun.h"
#include "SimpleShooterGameModeBase.h"
#include "Components/CapsuleComponent.h"


// Sets default values
AShooterCharacter::AShooterCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

	for (TSubclassOf<AWeaponBase> WeaponClass : DefaultWeapons)
	{
		if (!WeaponClass) continue;
		FActorSpawnParameters Params;
		AWeaponBase* SpawnedWeapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass, Params);
		int32 Index = Weapons.Add(SpawnedWeapon);
		if (Index == CurrentIndex)
		{
			CurrentWeapon = SpawnedWeapon;
		}
	}
	
	if (CurrentWeapon)
	{
		CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weapon_r"));
		CurrentWeapon->Mesh->SetVisibility(true);
		CurrentWeapon->SetOwner(this);
	}
}

bool AShooterCharacter::IsDead() const
{
	return Health <= 0;
}

float AShooterCharacter::GetHealthPercent() const
{
	return Health / MaxHealth;
}

int32 AShooterCharacter::GetCurrentWeaponAmmo() const
{
	if (CurrentWeapon)
	{
		return CurrentWeapon->GetRemainingAmmo();
	}
	return 0;
}

void AShooterCharacter::EquipWeapon(int32 index)
{
	if (!Weapons.IsValidIndex(index) || CurrentWeapon == Weapons[index]) return;

	CurrentIndex = index;
	CurrentWeapon = Weapons[index];
}


// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Move"), this, &AShooterCharacter::Move);
	PlayerInputComponent->BindAxis(TEXT("Strafe"), this, &AShooterCharacter::Strafe);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AShooterCharacter::LookUpRate);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Pressed, this, &AShooterCharacter::Shoot);
	PlayerInputComponent->BindAction(TEXT("Next Weapon"), IE_Pressed, this, &AShooterCharacter::NextWeapon);
	PlayerInputComponent->BindAction(TEXT("Last Weapon"), IE_Pressed, this, &AShooterCharacter::LastWeapon);
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                    AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health = Health - DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);


	if (IsDead())
	{
		ASimpleShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
		if (GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return DamageToApply;
}


void AShooterCharacter::Move(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::Strafe(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::NextWeapon()
{
	int32 index = Weapons.IsValidIndex(CurrentIndex + 1) ? CurrentIndex + 1 : 0;
	EquipWeapon(index);
}

void AShooterCharacter::LastWeapon()
{
	int32 index = Weapons.IsValidIndex(CurrentIndex + 1) ? CurrentIndex + 1 : Weapons.Num() - 1;
	EquipWeapon(index);
}


void AShooterCharacter::Shoot()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->PullTrigger();
	}
}

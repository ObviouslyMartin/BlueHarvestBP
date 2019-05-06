// Fill out your copyright notice in the Description page of Project Settings.

#include "Ship.h"


AShip::AShip():
  Super::AEnemy(),
  PosRelToPlayer(500, 0, 0),
  PosTolerance(50),
  MaxSpeed(20),
  Acceleration(10),
  ShootRate(1)
{
    AIControllerClass = AShipAI::StaticClass();
//    ShotMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShotMesh"));
//    ShotCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ShotCollider"));
    ShotTemplate = CreateDefaultSubobject<UProjectile>(TEXT("ShotTemplate"));
    AddOwnedComponent(ShotTemplate);
//    ShotTemplate->SetOwner(this);
//    auto AttachRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, false);
//    ShotTemplate->AttachToComponent(RootComponent, AttachRules);
//    AddOwnedComponent(ShotTemplate);
}

void AShip::BeginPlay()
{
    Super::BeginPlay();

    
//    SetActorHiddenInGame(true);
    
    // Disables collision components
    SetActorEnableCollision(false);

}

//Allows others to deal damage to this
float AShip::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}

//AShip* AShip::SpawnFromTemplate(const FVector& Location, AShip* const& Template, AActor* Owner)
//{
//    FActorSpawnParameters SpawnParams;
//    SpawnParams.Template = Template;
//    SpawnParams.Owner = Owner;
//
////    auto NewShip = Owner->GetWorld()->SpawnActor<AShip>(Location, FRotator(0), SpawnParams);
//////    auto NewShip = Owner->GetWorld()->SpawnActor(AShip::StaticClass(), Location, FRotator(0), SpawnParams);
//    return Template;
//}

float AShip::DealDamage(const float &Damage, AActor* const& Target, TSubclassOf <class UDamageType> DamageTypeClass)
{
    return Super::DealDamage(Damage, Target, DamageTypeClass);
}

void AShip::Die()
{
    Super::Die();
}

FRotator AShip::FacePlayer(const float& RotAmount)
{//so friends can call it
    return Super::FacePlayer(RotAmount);
}

bool AShip::facingPlayer(const float& Tolerance) const
{//so friends can call it
    return Super::facingPlayer(Tolerance);
}

bool AShip::facingPlayer() const
{//so friends can call it
    return Super::facingPlayer();
}

void AShip::Shoot()
{
    /*static auto NewComponent = */
    UProjectile::SpawnFromTemplate(GetVelocity() + GetActorForwardVector() * ShotTemplate->getStartSpeed(), ShotTemplate, this);
    
}




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
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
//    ShotTemplate->SetOwner(this);
//    auto AttachRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, false);
//    ShotTemplate->AttachToComponent(RootComponent, AttachRules);
//    AddOwnedComponent(ShotTemplate);
}

void AShip::BeginPlay()
{
    Super::BeginPlay();

    ShotTemplate->SetVisibility(false, true);
    ShotTemplate->SetCollisionEnabled(ECollisionEnabled::NoCollision);
//    SetActorHiddenInGame(true);
    // Disables collision components
//    SetActorEnableCollision(false);
    SpawnDefaultController();

}

AShip* AShip::SpawnFromTemplate(const FVector& StartPos, AActor* InOwner)
{
    FActorSpawnParameters SpawnParams;
    SpawnParams.Template = this;
    if (InOwner) { SpawnParams.Owner = InOwner; }
    auto NewShip = GetWorld()->SpawnActor<AShip>(StartPos, FRotator(0), SpawnParams);
    {
        NewShip->SetActorHiddenInGame(false);
        NewShip->SetActorEnableCollision(true);
        
        InitializeComponents();
        NewShip->Mesh->SetWorldLocation(NewShip->GetActorLocation());
        NewShip->Collider->SetWorldLocation(NewShip->GetActorLocation());
        
    }
    return NewShip;
}

void AShip::InitShip (FVector InPosRelToPlayer, float InPosTolerance, float InMaxSpeed, float InAcceleration, float InShootRate, UProjectile* InShotTemplate, USceneComponent* InTargetComponent)
{
    if(!InitdShip)
    {
        PosRelToPlayer = InPosRelToPlayer;
        PosTolerance = InPosTolerance;
        MaxSpeed = InMaxSpeed;
        Acceleration = InAcceleration;
        ShootRate = InShootRate;
        ShotTemplate = InShotTemplate;
        TargetComponent = InTargetComponent;
        auto ShipController = Cast<AShipAI>(GetController());
        if(ShipController) { ShipController->SetShotDelayFromRate(ShootRate); }
        
        InitializeComponents();
        Mesh->SetWorldLocation(GetActorLocation());
        Collider->SetWorldLocation(GetActorLocation());
        
        InitdShip = true;
    }
}

//Allows others to deal damage to this
float AShip::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}

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




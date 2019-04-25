// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"

// Sets default values
AProjectile::AProjectile() : Acceleration(0)
{
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
    Driver = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Driver"));
}

void AProjectile::Initialize(FVector StartVelocity, USceneComponent* Target, float HomingAccel, float Acceleration)
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    
    this->Acceleration = FVector(Acceleration);
    
    
    Driver->Velocity = StartVelocity;
    Driver->bIsHomingProjectile = HomingAccel;
    Driver->HomingAccelerationMagnitude = HomingAccel;
    Driver->HomingTargetComponent = Target;
    
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
    Super::BeginPlay();
    
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    Driver->Velocity += (Acceleration/DeltaTime);
    
}




// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"

// Sets default values
AProjectile::AProjectile() : Acceleration(0)
{
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(RootComponent);
    Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
    Collider->SetupAttachment(RootComponent);
    Driver = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Driver"));
    
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
    if (SphereVisualAsset.Succeeded())
    {
        Mesh->SetStaticMesh(SphereVisualAsset.Object);
    }
}

void AProjectile::Initialize(FVector StartVelocity, USceneComponent* Target, float HomingAccel, FVector Acceleration)
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    
    this->Acceleration = FVector(Acceleration);
    
//    Driver->SetUpdatedComponent(RootComponent);
//    Driver->bSimulationEnabled = true;
    
    Driver->ProjectileGravityScale = 0;
    Driver->Velocity = StartVelocity;
    Driver->UpdateComponentVelocity();
    Driver->bIsHomingProjectile = bool(HomingAccel);
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
    Driver->UpdateComponentVelocity();

    
}




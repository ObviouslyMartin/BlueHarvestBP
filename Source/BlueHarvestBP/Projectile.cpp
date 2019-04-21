// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"

// Sets default values
AProjectile::AProjectile():
    Velocity(1),
    Acceleration(0),
    HomingFactor(1),
    Target(NULL)
{

}

AProjectile::AProjectile(FVector StartVelocity, AActor* Target, float HomingFactor, float Acceleration):
    Velocity(StartVelocity),
    Acceleration(Acceleration),
    HomingFactor(HomingFactor),
    Target(Target)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
//    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
//    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
//    Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
    
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
    if(Acceleration) { Velocity *= Acceleration; }
    if(Target)
    {
        auto newDir = TargetDir();
        auto forward = GetActorForwardVector();
        auto turnCheck = FVector::DotProduct(forward, newDir);
        if(turnCheck < HomingFactor)
        {
            newDir = (newDir * HomingFactor).GetSafeNormal();
        }
        Velocity = newDir * Velocity.Size();
        
    }
    
}

FVector  AProjectile::TargetDir()
{
    return (Target->GetActorLocation() - GetActorLocation()).GetSafeNormal();
}

FVector VecAddFloat(FVector Vec, const float& InF)
{
    Vec.X += InF;
    Vec.Y += InF;
    Vec.Z += InF;
    return Vec;
}

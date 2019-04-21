// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"

// Sets default values
AEnemy::AEnemy():
    MaxHealth(50),
    CurrentHealth(MaxHealth),
    FireRate(0.25)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    
//    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
//    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
//    Collider = CreateDefaultSubobject<UShapeComponent>(TEXT("Collider"));
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
    Super::BeginPlay();
    
    Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	
}

float AEnemy::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);;
}

void AEnemy::DealDamage(float damage, AActor* target, DmgType type)
{
    target->TakeDamage(damage, FDamageEvent(), GetInstigatorController(), this);

}

void AEnemy::Die()
{
    
}

FRotator AEnemy::FacePlayer()
{
    FRotator RotToPlayer = (Player->GetActorLocation() - GetActorLocation()).Rotation();
    SetActorRotation(RotToPlayer);
    
    return RotToPlayer;
}

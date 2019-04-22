// Fill out your copyright notice in the Description page of Project Settings.

#include "Ship.h"


AShip::AShip() : Super::AEnemy()
{
    AIControllerClass = AShipAI::StaticClass();
}

void AShip::BeginPlay()
{
    
}

//Allows others to deal damage to this
float AShip::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
    
    return float();
}

void AShip::DealDamage(float Damage, AActor* Target, DmgType Type)
{
    Super::DealDamage(Damage, Target, Type);
}

void AShip::Die()
{
    Super::Die();
}

FRotator AShip::FacePlayer()
{
    Super::FacePlayer();
    
    return FRotator();
}

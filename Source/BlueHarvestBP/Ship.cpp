// Fill out your copyright notice in the Description page of Project Settings.

#include "Ship.h"


AShip::AShip():
  Super::AEnemy(),
  PosRelToPlayer(500, 0, 0),
  PosTolerance(50),
  MaxSpeed(20),
  Acceleration(10)
{
    AIControllerClass = AShipAI::StaticClass();
    
}

void AShip::BeginPlay()
{
    Super::BeginPlay();
//    if (GEngine) { GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Orange, FString::Printf(TEXT("Possessed: %s"), ((GetController()? TEXT("true"):TEXT("false") )))); }

}

//Allows others to deal damage to this
float AShip::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
    
    return float();
}

void AShip::DealDamage(float Damage, AActor* Target, DamageType Type)
{
    Super::DealDamage(Damage, Target, Type);
}

void AShip::Die()
{
    Super::Die();
}

FRotator AShip::FacePlayer(float RotAmount)
{
    return Super::FacePlayer(RotAmount);
}





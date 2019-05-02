// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "ShipAI.h"
#include "Ship.generated.h"

/**
 * 
 */
UCLASS()
class BLUEHARVESTBP_API AShip : public AEnemy
{
	GENERATED_BODY()
public:
    AShip();
    
    //Allows others to deal damage to this
    virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
    
    
protected:
    virtual void BeginPlay() override;

    virtual void DealDamage(float Damage, AActor* Target, DamageType Type) override;
    virtual void Die() override;
    virtual FRotator FacePlayer(float RotAmount) override;

    UPROPERTY(EditAnywhere, Category = "Stats")
    FVector PosRelToPlayer;
    UPROPERTY(EditAnywhere, Category = "Stats")
    float PosTolerance;
    UPROPERTY(EditAnywhere, Category = "Stats")
    float MaxSpeed;
    UPROPERTY(EditAnywhere, Category = "Stats")
    float Acceleration;
    
    friend class AShipAI;
};

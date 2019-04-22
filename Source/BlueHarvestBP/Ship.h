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
    
    virtual void BeginPlay() override;
    
    //Allows others to deal damage to this
    virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
    
    
private:
    virtual void DealDamage(float Damage, AActor* Target, DmgType Type) override;
    virtual void Die() override;
    virtual FRotator FacePlayer() override;
    
};

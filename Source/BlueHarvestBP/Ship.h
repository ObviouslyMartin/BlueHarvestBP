// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Core/Public/Misc/OutputDeviceNull.h"
#include "Enemy.h"

#include "ShipAI.h"
#include "Projectile.h"

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
    
    USceneComponent* TargetComponent;
    
protected:
    friend class AShipAI;
    
    virtual void BeginPlay() override;

    virtual float DealDamage(const float &Damage, AActor* const& Target, TSubclassOf < class UDamageType > DamageTypeClass) override;
    virtual void Die() override;
    virtual FRotator FacePlayer(const float& RotAmount) override;
    virtual bool facingPlayer(const float& Tolerance) const override;
    virtual bool facingPlayer() const override;
    
    // Ship Stats
    UPROPERTY(EditAnywhere, Category = "Stats")
    FVector PosRelToPlayer;
    UPROPERTY(EditAnywhere, Category = "Stats")
    float PosTolerance;
    UPROPERTY(EditAnywhere, Category = "Stats")
    float MaxSpeed;
    UPROPERTY(EditAnywhere, Category = "Stats")
    float Acceleration;
    UPROPERTY(EditAnywhere, Category = "Stats")
    float ShootRate;

    UPROPERTY(EditAnywhere, Category = "Components")
    UProjectile* ShotTemplate;
    virtual void Shoot();
    
    
};

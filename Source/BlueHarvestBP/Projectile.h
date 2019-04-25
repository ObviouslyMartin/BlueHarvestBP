// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Projectile.generated.h"

UCLASS()
class BLUEHARVESTBP_API AProjectile : public APawn
{
	GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
//    UPROPERTY(BlueprintCallable)
    AProjectile();
    
    // StartVelocity is initial direction and speed
    // Homing time is time it takes to rotate 90 degrees
    // acceleration is multiplier for speed
//    UPROPERTY(BlueprintCallable)
    void Initialize(FVector StartVelocity, USceneComponent* Target, float HomingAccel, float Acceleration);
    
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    
protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
    UPROPERTY(EditAnywhere, Category = "Components")
    UStaticMeshComponent* Mesh;
    UPROPERTY(EditAnywhere, Category = "Components")
    UCapsuleComponent* Collider;
    
    UProjectileMovementComponent* Driver;
    
    FVector Acceleration;
};

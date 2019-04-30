// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Projectile.generated.h"

UCLASS(ClassGroup="BlueHarvest")
class BLUEHARVESTBP_API AProjectile : public APawn
{
	GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
//    UPROPERTY(BlueprintCallable)
//    UFUNCTION(BlueprintCallable)
    AProjectile();
    
    // StartVelocity is initial direction and speed
    // Homing time is time it takes to rotate 90 degrees
    // acceleration is added to the velocity over the course of one second
    UFUNCTION(BlueprintCallable)
//    UPROPERTY(Category = "Projectile")
    void Initialize(FVector StartVelocity, USceneComponent* Target, float HomingAccel, FVector Acceleration);
    
    // Called every frame
    UFUNCTION(BlueprintCallable)
    virtual void Tick(float DeltaTime) override;
    
protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
    UPROPERTY(EditAnywhere, Category = "Projectile")
    UStaticMeshComponent* Mesh;
    UPROPERTY(EditAnywhere, Category = "Projectile")
    UCapsuleComponent* Collider;
    
    UProjectileMovementComponent* Driver;
    
    UPROPERTY(EditAnywhere, Category = "Projectile")
    FVector Acceleration;
};

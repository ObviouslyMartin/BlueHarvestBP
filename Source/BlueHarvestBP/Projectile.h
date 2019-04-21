// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Projectile.generated.h"

UCLASS()
class BLUEHARVESTBP_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
    AProjectile();
    
    // StartVelocity is initial direction and speed
    // Homing time is time it takes to rotate 90 degrees
    // acceleration is multiplier for speed
	AProjectile(FVector StartVelocity, AActor* Target, float HomingFactor, float Acceleration);

    // Called every frame
    virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    UPROPERTY(EditAnywhere, Category = "Components")
    UStaticMeshComponent* Mesh;
    UPROPERTY(EditAnywhere, Category = "Components")
    UCapsuleComponent* Collider;
    
    FVector Velocity;
    float Acceleration;
    float HomingFactor;
    
    AActor* Target;
    
    FVector TargetDir();
    
    
    


};

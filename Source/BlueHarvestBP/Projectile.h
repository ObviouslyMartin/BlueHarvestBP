// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//base includes
#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
//added unreal includes
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/CapsuleComponent.h"
//added custom includes

//must be last
#include "Projectile.generated.h"

UCLASS( Blueprintable, BlueprintType, ClassGroup="BlueHarvest", meta=(BlueprintSpawnableComponent) ) class BLUEHARVESTBP_API UProjectile : public UPrimitiveComponent
{
	GENERATED_BODY()
	
public:
    // Sets default values for this pawn's properties
    //    UPROPERTY(BlueprintCallable)
    //    UFUNCTION(BlueprintCallable)
    UProjectile();
    
    // StartVelocity is initial direction and speed
    // Homing time is time it takes to rotate 90 degrees
    // acceleration is added to the velocity over the course of one second
    UFUNCTION(BlueprintCallable)
    static UProjectile* SpawnFromTemplate(const FVector& StartVelocity, UProjectile* const& Template, AActor* Owner);
    UFUNCTION(BlueprintCallable)
    virtual void Init(const FVector& StartVelocity, USceneComponent* Target, const float& HomingAccel = 0, const float& Acceleration = 0, UStaticMeshComponent* Mesh = NULL, UCapsuleComponent* Collider = NULL);
            //    virtual void CopyFrom(Uprojectile OtherProjectile);
    //Same as above except uses StartRotation and StartSpeed instead of StartVelocity
//    UFUNCTION(BlueprintCallable)
//    virtual void Initialize(const FRotator& StartRotation, USceneComponent* Target, const float& HomingAccel = 0, const float& Acceleration = 0, UStaticMeshComponent* Mesh = NULL, UCapsuleComponent* Collider = NULL);
    UFUNCTION(BlueprintCallable)
    virtual void SetTarget(USceneComponent* const& Target);
    UFUNCTION(BlueprintCallable)
    virtual void SetVelocity(const FVector& Velocity);
    UFUNCTION(BlueprintCallable)
    virtual void InitRotation(const FRotator& Rotation, const bool& ResetSpeed = true);
    UFUNCTION(BlueprintCallable)
    virtual float getStartSpeed() const;
    
    
protected:
    USceneComponent* RootComponent;

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
    UPROPERTY(EditAnywhere, Category = "Components")
    UStaticMeshComponent* Mesh;
    UPROPERTY(EditAnywhere, Category = "Components")
    UCapsuleComponent* Collider;
    
    UProjectileMovementComponent* Driver;
    
    UPROPERTY(EditAnywhere, Category = "Stats")
    float StartSpeed;
//    FVector StartVel;
    UPROPERTY(EditAnywhere, Category = "Stats")
    float HomingAccel;
    UPROPERTY(EditAnywhere, Category = "Stats")
    float Acceleration;
    
    UFUNCTION(BlueprintCallable)
    void MessageDebug() const;
    FTimerHandle DebugTimer;
    
    
private:
    // Called every frame
//    UFUNCTION(BlueprintCallable)
//    virtual void Tick(float DeltaTime) override;
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/DamageType.h"


#include "Enemy.generated.h"

UCLASS()
class BLUEHARVESTBP_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy();
    
    //Allows others to deal damage to this
    UFUNCTION(BlueprintCallable)
    virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
    
    UFUNCTION(BlueprintCallable)
    float GetHealth() const;
    UFUNCTION(BlueprintCallable)
    float GetMaxHealth() const;
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    virtual float DealDamage(const float &Damage, AActor* const& Target, TSubclassOf < class UDamageType > DamageTypeClass);
    virtual void Die();
    virtual FRotator FacePlayer(const float &RotAmount);
    virtual bool facingPlayer(const float &Tolerance) const;
    virtual bool facingPlayer() const;
    
    AActor* Player;
//    TSubclassOf<class APawn> PlayerClass;
    UPROPERTY(EditAnywhere, Category = "Components")
    UStaticMeshComponent* Mesh;
    UPROPERTY(EditAnywhere, Category = "Components")
    UCapsuleComponent* Collider;
    
    UPROPERTY(EditAnywhere, Category = "Stats")
    float RotSpeed;
    UPROPERTY(EditAnywhere, Category = "Stats")
    float MaxHealth;
    float CurrentHealth;
    UPROPERTY(EditAnywhere, Category = "Stats")
    float FacingTolerance;
    UPROPERTY(EditAnywhere, Category = "Stats")
    float BaseDamage;
    UPROPERTY(EditAnywhere, Category = "Stats")
    float AimTolerance;
    //Array of defences/damage multipliers. User is expected to specify no  more than (number of damage types).
    //  Fixed-size arrays cannot be exposed to the editor
    //  Extra entrees will be discarded. Non-specified entries will be set to one.
//    UPROPERTY(EditAnywhere, Category = "Stats")
//    TArray<float> DmgMultipliers;
    
    friend class AEnemyAI;
    
};

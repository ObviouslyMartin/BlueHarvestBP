// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"



#include "Enemy.generated.h"

//Normal is also the count - 1, so Normal must remain LAST
//Do NOT specify values, they must be from 0 to Normal - 1
//UPROPERTY(VisibleAnywhere)
enum class DmgType : uint8 { Normal UMETA(DisplayName="Normal") };


UCLASS()
class BLUEHARVESTBP_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy();
    
    //Allows others to deal damage to this
    virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
    
    float GetHealth() const;
    float GetMaxHealth() const;
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    virtual void DealDamage(float Damage, AActor* Target, DmgType Type);
    virtual void Die();
    virtual FRotator FacePlayer();
    
    AActor* Player;
    UPROPERTY(EditAnywhere, Category = "Components")
    UStaticMeshComponent* Mesh;
    UPROPERTY(EditAnywhere, Category = "Components")
    UCapsuleComponent* Collider;
    
    UPROPERTY(EditAnywhere, Category = "Stats")
    float MaxHealth;
    float CurrentHealth;
    UPROPERTY(EditAnywhere, Category = "Stats")
    float FireRate;
    UPROPERTY(EditAnywhere, Category = "Stats")
    float BaseDamage;
    //Array of defences/damage multipliers. User is expected to specify no  more than (number of damage types).
    //  Fixed-size arrays cannot be exposed to the editor
    //  Extra entrees will be discarded. Non-specified entries will be set to one.
    UPROPERTY(EditAnywhere, Category = "Stats")
    TArray<float> DmgMultipliers;
    
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"



#include "Enemy.generated.h"

enum class DmgType : uint8 { Normal UMETA(DisplayName="Normal") };


UCLASS()
class BLUEHARVESTBP_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy();
    
    

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    virtual void DealDamage(float damage, AActor* target, DmgType type);
    virtual void Die();
    virtual FRotator FacePlayer();
    
    AActor* Player;
    UPROPERTY(EditAnywhere, Category = "Components")
    UStaticMeshComponent* Mesh;
    UPROPERTY(EditAnywhere, Category = "Components")
    UCapsuleComponent* Collider;
    
    UPROPERTY(EditAnywhere, Category = "Stats")
    float MaxHealth;
    UPROPERTY(EditAnywhere, Category = "Stats")
    float CurrentHealth;
    UPROPERTY(EditAnywhere, Category = "Stats")
    float FireRate;
    UPROPERTY(EditAnywhere, Category = "Stats")
    float BaseDamage;
    
public:
    //Allows others to deal damage to this
    virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

};

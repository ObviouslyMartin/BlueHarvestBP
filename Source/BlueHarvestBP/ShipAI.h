// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAI.h"
#include "ShipAI.generated.h"

/**
 * 
 */
UCLASS()
class BLUEHARVESTBP_API AShipAI : public AEnemyAI
{
    GENERATED_BODY()
    
public:
    AShipAI();
    
protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    virtual void Possess(APawn* Pawn) override;
    
    virtual FVector Position();
    virtual bool isPositioned();
    UPROPERTY(EditAnywhere, Category = "Stats")
    FVector RelPlayerPos;
    UPROPERTY(EditAnywhere, Category = "Stats")
    float PosTollerance;
    
};

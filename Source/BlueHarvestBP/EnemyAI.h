// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "Enemy.h"

#include "EnemyAI.generated.h"

enum class EAIState : uint8 { Start UMETA(DisplayName="Start"), Positioning UMETA(DisplayName = "Positioning"), Attack UMETA(DisplayName = "Attack"), Idle UMETA(DisplayName = "Idle"), Leaving UMETA(DisplayName = "Leaving"), Dead UMETA(DisplayName = "Dead") };

UCLASS()
class BLUEHARVESTBP_API AEnemyAI : public AAIController
{
	GENERATED_BODY()
	
public:
    AEnemyAI();
    
protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    virtual void Possess(APawn* Pawn) override;
    
    APawn* PossessedPawn;
    AActor* Player;

    
    EAIState AIState;
};

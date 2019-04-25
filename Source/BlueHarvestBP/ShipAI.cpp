// Fill out your copyright notice in the Description page of Project Settings.

#include "ShipAI.h"


AShipAI::AShipAI() : AEnemyAI()
{
    
}

// Called when the game starts or when spawned
void AShipAI::BeginPlay()
{
    Super::BeginPlay();
    
}

// Called every frame
void AShipAI::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    switch(AIState)
    {
        case EAIState::Start:
            
            break;
            
        case EAIState::Positioning:
            
            break;
            
        case EAIState::Attack:
            
            break;
            
        case EAIState::Idle:
            
            break;
            
        case EAIState::Dead:
            
            break;
    }
}

void AShipAI::Possess(APawn* Pawn)
{
    Super::Possess(Pawn);
    
}

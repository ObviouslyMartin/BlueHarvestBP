// Fill out your copyright notice in the Description page of Project Settings.

#include "ShipAI.h"
#include "Enemy.h"

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
            AIState = EAIState::Positioning;
            break;
            
        case EAIState::Positioning:
            
            break;
            
        case EAIState::Attack:
            
            break;
            
        case EAIState::Idle:
            
            break;
            
        case EAIState::Leaving:
            
            break;
            
        case EAIState::Dead:
            
            break;
    }
}

void AShipAI::Possess(APawn* Pawn)
{
    Super::Possess(Pawn);
    
}

FVector AShipAI::Position()
{
    auto Dest = Player->GetActorLocation() + RelPlayerPos;
    MoveToLocation(Dest);
    return Dest;
}

bool AShipAI::isPositioned()
{
    FVector PosDiff = (Player->GetActorLocation() + RelPlayerPos) - PossessedPawn->GetActorLocation();
    return PosTollerance >= PosDiff.Size();
}

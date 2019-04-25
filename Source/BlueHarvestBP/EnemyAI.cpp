// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAI.h"

AEnemyAI::AEnemyAI()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    
}

// Called when the game starts or when spawned
void AEnemyAI::BeginPlay()
{
    Super::BeginPlay();
    AIState = EAIState::Start;
}

// Called every frame
void AEnemyAI::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
}

void AEnemyAI::Possess(APawn* Pawn)
{
    Super::Possess(Pawn);
    PossessedPawn = Pawn;
    
}



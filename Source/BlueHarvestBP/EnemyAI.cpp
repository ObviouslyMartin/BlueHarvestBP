// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAI.h"
#include "Enemy.h"

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
    Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

// Called every frame
void AEnemyAI::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AEnemyAI::Possess(APawn* Pawn)
{
    Super::Possess(Pawn);
    Enemy = (AEnemy*) Pawn;
    if (Enemy)
    {
        RotSpeed = Enemy->RotSpeed;
    }
    
}


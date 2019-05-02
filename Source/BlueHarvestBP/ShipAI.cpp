// Fill out your copyright notice in the Description page of Project Settings.

#include "ShipAI.h"
#include "Ship.h"
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
            AIState = EAIState::Position;
            break;
            
        case EAIState::Position:
            if (isPositioned(0)) { AIState = EAIState::Attack; }
            else if (Ship) { PositionShip(Ship->MaxSpeed * DeltaTime, true); }
            break;
            
        case EAIState::Attack:
                PositionShip(Ship->MaxSpeed * DeltaTime);
                if (Ship) { Ship->FacePlayer(RotSpeed * DeltaTime); }
            break;
            
        case EAIState::Idle:
            
            break;
            
        case EAIState::Leave:
            
            break;
            
        case EAIState::Dead:
            
            break;
    }
}

void AShipAI::Possess(APawn* Pawn)
{
    Super::Possess(Pawn);
    Ship = Cast<AShip>(Enemy);
}

void AShipAI::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
    Super::OnMoveCompleted(RequestID, Result);
    AIState = EAIState::Attack;
}

FVector AShipAI::PositionShip(float MoveSize, bool FaceForward)
{
    auto Dest = FVector(0);
    if (Player)
    {
        Dest = Player->GetActorLocation();
    }
    if (Ship) { Dest += Ship->PosRelToPlayer; }
//    if(GetMoveStatus() == EPathFollowingStatus::Idle)
//    {
//        MoveToLocation(Dest, 0);
//    }
//    AActor::AddActorLocalOffset(PosdEnemy->GetActorLocation() - Dest);
    if (Enemy)
    {
        auto CurrLoc = Enemy->GetActorLocation();
        auto PosDiff = Dest - CurrLoc;
        auto Move = PosDiff.GetSafeNormal() * MoveSize;
        FVector* NewPos;
        if (PosDiff.Size() < Move.Size())
        {//would move too far, move into place instead
            NewPos = &Dest;
            AIState = EAIState::Attack;
        }
        else
        {//not in place yet
            Move += Enemy->GetActorLocation();
            NewPos = &(Move);
        }
        Enemy->SetActorLocation(*NewPos);
        if (FaceForward) { Enemy->SetActorRotation(PosDiff.Rotation()); }
    }
    
    return Dest;
}

bool AShipAI::isPositioned(float Tolerance)
{
    auto PlayerLoc = FVector(0);
    if (Player) { PlayerLoc = Player->GetActorLocation(); }
    auto PawnLoc = FVector(0);
    if (Enemy) { PawnLoc = Enemy->GetActorLocation(); }
    FVector PosDiff = PlayerLoc - PawnLoc;
    if (Ship)
    {
        PosDiff += Ship->PosRelToPlayer;
    }
//    if (GEngine)
//    {
//        GEngine->AddOnScreenDebugMessage(3, 1.f, FColor::Orange, FString::Printf(TEXT("\n\n\n\nPosDiff: %f"),PosDiff.Size()));
//        GEngine->AddOnScreenDebugMessage(4, 1.f, FColor::Orange, FString::Printf(TEXT("PlayerLoc: %f"),PlayerLoc.Size()));
//        GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Orange, FString::Printf(TEXT("PawnLoc: %f"),PawnLoc.Size()));
//    }
    return Tolerance >= PosDiff.Size();
}

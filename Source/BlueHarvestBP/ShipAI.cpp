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
            if (isPositioned()) { AIState = EAIState::Attack; }
            else { MoveIntoPosition(MaxSpeed * DeltaTime); }
            break;
            
        case EAIState::Attack:
            if (!isPositioned()) { AIState = EAIState::Position; }
            else
            {
                MatchPlayerVel();
                auto PossessedShip = (AShip*)PossessedPawn;
                if (PossessedShip && Player) { PossessedShip->FacePlayer(RotSpeed/DeltaTime); }
            }
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
    auto PossessedShip = (AShip*)Pawn;
    if(PossessedShip)
    {
        RelPlayerPos = PossessedShip->RelPlayerPos;
        PosTollerance = PossessedShip->PosTollerance;
        MaxSpeed = PossessedShip->MaxSpeed;
        Acceleration = PossessedShip->Acceleration;
    }
}

void AShipAI::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
    Super::OnMoveCompleted(RequestID, Result);
    AIState = EAIState::Attack;
}

FVector AShipAI::MoveIntoPosition(float MoveSize)
{
    auto Dest = FVector(0);
    if (Player)
    {
        Dest = Player->GetActorLocation();
    }
    Dest += RelPlayerPos;
//    if (GEngine) { GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Orange, FString::Printf(TEXT("Dest: %f, %f, %f"),Dest.X, Dest.Y, Dest.Z)); }
//    if(GetMoveStatus() == EPathFollowingStatus::Idle)
//    {
//        MoveToLocation(Dest, 0);
//    }
//    AActor::AddActorLocalOffset(PossessedPawn->GetActorLocation() - Dest);
    auto CurrLoc = PossessedPawn->GetActorLocation();
    auto PosDiff = Dest - CurrLoc;
    auto Move = PosDiff.GetSafeNormal() * MoveSize;
    FVector* NewPos;
    if (GEngine) { GEngine->AddOnScreenDebugMessage(2, 1.f, FColor::Orange, FString::Printf(TEXT("PosDiff: %f, Move: %f"),PosDiff.Size(), Move.Size())); }
    if (PosDiff.Size() < Move.Size())
    {//would move too far, move into place instead
        NewPos = &Dest;
        AIState = EAIState::Attack;
    }
    else
    {//not in place yet
        Move += PossessedPawn->GetActorLocation();
        NewPos = &(Move);
    }
    PossessedPawn->SetActorLocation(*NewPos);
    PossessedPawn->SetActorRotation(PosDiff.Rotation());
    
    return Dest;
}

bool AShipAI::isPositioned()
{
    auto PlayerLoc = FVector(0);
    if (Player) { Player->GetActorLocation(); }
    auto PawnLoc = FVector(0);
    if (PossessedPawn) { PawnLoc = PossessedPawn->GetActorLocation(); }
    auto PossessedShip = (AShip*)PossessedPawn;
    FVector PosDiff = (PlayerLoc + PossessedShip->RelPlayerPos) - PawnLoc;
    return PosTollerance >= PosDiff.Size();
}

void AShipAI::MatchPlayerVel()
{
    auto PossessedShip = (AShip*)PossessedPawn;
    if (Player && PossessedShip)
    {
//        AActor::AddActorLocalOffset(Player->GetVelocity());
        PossessedShip->SetActorLocation(Player->GetActorLocation() + RelPlayerPos);
    }
}

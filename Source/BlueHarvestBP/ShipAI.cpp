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
    ShotDelay = ((Ship->ShootRate)? 1/Ship->ShootRate : 1);
//    auto ShotDelay = Ship->ShootRate;
//
//    FTimerDelegate ShootDelegate;
//    ShootDelegate.BindUFunction(this, FName("ShootRoutune"), ShotTimer);
//    GetWorldTimerManager().SetTimer(ShotTimer, ShootDelegate, ShotDelay, true);
//    GetWorldTimerManager().PauseTimer(ShotTimer);
    
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
            /*if (isPositioned(0)) { AIState = EAIState::Attack; }
            else */if (Ship) { PositionShip(Ship->MaxSpeed * DeltaTime, true); }
            break;
            
        case EAIState::Attack:
            PositionShip(Ship->MaxSpeed * DeltaTime);
            if (Ship) { Ship->FacePlayer(RotSpeed * DeltaTime); }

//            if(GetWorldTimerManager().IsTimerPaused(ShotTimer))
//            {
//                int i = 0;
//            }
            
            //    GetWorldTimerManager().PauseTimer(ShotTimer);
            if(((!GetWorldTimerManager().IsTimerActive(ShotTimer)) && Ship) && Ship->facingPlayer())
            {
//                GetWorldTimerManager().UnPauseTimer(ShotTimer);
                Ship->Shoot();
                GetWorldTimerManager().SetTimer(ShotTimer, ShotDelay, false);

            }
//            if(GetWorldTimerManager().IsTimerPaused(ShotTimer) && Ship->facingPlayer())
//            {
//                GetWorldTimerManager().UnPauseTimer(ShotTimer);
//
//            }

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
    if (Player && Ship)
    {
        Dest =  Player->GetActorLocation();
        Dest += Player->GetActorForwardVector() * Ship->PosRelToPlayer.X;
        Dest += Player->GetActorRightVector()   * Ship->PosRelToPlayer.Y;
        Dest += Player->GetActorUpVector()      * Ship->PosRelToPlayer.Z;
    }
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
        
//*NewPos = FVector(0);
        
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

    return Tolerance >= PosDiff.Size();
}

//void AShipAI::ShootRoutine(FTimerHandle Timer)
//{
//
//    if (Ship) { Ship->Shoot(); }
////    GetWorldTimerManager().SetTimer(Timer, ShootDelegate, Delay, true);
//    GetWorldTimerManager().PauseTimer(Timer);
//}

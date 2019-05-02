// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"

// Sets default values
AEnemy::AEnemy():
  RotSpeed(90),
  MaxHealth(50),
  CurrentHealth(MaxHealth),
  FireRate(0.25)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(RootComponent);
    Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
    Collider->SetupAttachment(RootComponent);
}

float AEnemy::GetHealth() const
{
    return CurrentHealth;
}

float AEnemy::GetMaxHealth() const
{
    return MaxHealth;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
    Super::BeginPlay();
    
    Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    
    
    while((DmgMultipliers.Num() < (int(DamageType::Normal) + 1)))
    {
        DmgMultipliers.Add(1.0f);
    }
    DmgMultipliers.SetNum(int(DamageType::Normal) + 1, true);
	
}

float AEnemy::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);;
}

void AEnemy::DealDamage(float Damage, AActor* Target, DamageType Type)
{
    Target->TakeDamage(Damage, FDamageEvent(), GetInstigatorController(), this);

}

void AEnemy::Die()
{
    
}

FRotator AEnemy::FacePlayer(float RotAmount)
{
    if (!Player) { return FRotator(0); }
    auto ToPlayerVec =  Player->GetActorLocation() - GetActorLocation();
    auto PlayerRelativeRot = ToPlayerVec.Rotation();

    if (RotAmount == 0)
    {
        SetActorRotation(PlayerRelativeRot);
    }
    else
    {
        FVector RotAxis;
        if (GetActorForwardVector().Rotation().Equals((-ToPlayerVec).Rotation(), 10))
        {//if facing close to directly away from player
            RotAxis = GetActorUpVector();
        }
        else
        {
            RotAxis = FVector::CrossProduct(GetActorForwardVector(), ToPlayerVec).GetSafeNormal();
        }
        
        auto NewForward = GetActorForwardVector().RotateAngleAxis(RotAmount, RotAxis);
        auto NewForDot = FVector::DotProduct(GetActorForwardVector(), NewForward.GetSafeNormal());
        auto PlayerDot = FVector::DotProduct(GetActorForwardVector(), ToPlayerVec.GetSafeNormal());
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(4, 1.f, FColor::Orange, FString::Printf(TEXT("\n\n\n\n\nNewForDot: %f, PlayerDot: %f"),NewForDot, PlayerDot));
        }
        if (NewForDot < PlayerDot)
        {//if would rotate too far
            SetActorRotation(PlayerRelativeRot);
        }
        else
        {
            SetActorRotation(NewForward.Rotation());
        }
        
    }
    
    return PlayerRelativeRot;
}


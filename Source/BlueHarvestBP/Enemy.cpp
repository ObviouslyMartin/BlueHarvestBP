// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"

// Sets default values
AEnemy::AEnemy():
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
    
    Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    
    
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
    auto ToPlayerVec = Player->GetActorLocation() - GetActorLocation();
    auto PlayerRelativeRot = ToPlayerVec.Rotation();

    if (RotAmount == 0)
    {
        SetActorRotation(PlayerRelativeRot);
    }
    else
    {
        auto RotAxis = FVector::CrossProduct(ToPlayerVec, GetActorForwardVector());
        auto NewForward = GetActorForwardVector().RotateAngleAxis(RotAmount, RotAxis);
        if (FVector::DotProduct(GetActorForwardVector(), NewForward) > FVector::DotProduct(GetActorForwardVector(), ToPlayerVec))
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


// Fill out your copyright notice in the Description page of Project Settings.

#include "Ship.h"


AShip::AShip():
  Super::AEnemy(),
  PosRelToPlayer(500, 0, 0),
  PosTolerance(50),
  MaxSpeed(20),
  Acceleration(10),
  ShootRate(1)
{
    AIControllerClass = AShipAI::StaticClass();
//    ShotMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShotMesh"));
//    ShotCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ShotCollider"));
//    ShotTemplate = CreateDefaultSubobject<AProjectile>(TEXT("ShotTemplate"));
//    ShotTemplate->SetOwner(this);
//    auto AttachRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, false);
//    ShotTemplate->AttachToComponent(RootComponent, AttachRules);
//    AddOwnedComponent(ShotTemplate);
}

void AShip::BeginPlay()
{
    Super::BeginPlay();
//    if (GEngine) { GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Orange, FString::Printf(TEXT("Possessed: %s"), ((GetController()? TEXT("true"):TEXT("false") )))); }
    
//    SetActorHiddenInGame(true);
    
    // Disables collision components
    SetActorEnableCollision(false);
    
    // Stops the Actor from ticking
//    SetActorTickEnabled(false);

}

//Allows others to deal damage to this
float AShip::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}

float AShip::DealDamage(const float &Damage, AActor* const& Target, TSubclassOf < class UDamageType > DamageTypeClass)
{
    return Super::DealDamage(Damage, Target, DamageTypeClass);
}

void AShip::Die()
{
    Super::Die();
}

FRotator AShip::FacePlayer(const float& RotAmount)
{//so friends can call it
    return Super::FacePlayer(RotAmount);
}

bool AShip::facingPlayer(const float& Tolerance) const
{//so friends can call it
    return Super::facingPlayer(Tolerance);
}

bool AShip::facingPlayer() const
{//so friends can call it
    return Super::facingPlayer();
}

//void AShip::Shoot()
//{
//    FActorSpawnParameters SpawnParams;
//    SpawnParams.Instigator = Instigator;
//    SpawnParams.bNoFail = true;
//    SpawnParams.Owner = this;
////    SpawnParams.Template = ShotTemplate;
////    auto Shot = GetWorld()->SpawnActor<AProjectile>(AProjectile::StaticClass(), GetActorLocation() + GetActorForwardVector() * 100, GetActorRotation(), SpawnParams);
////    bool PlayerShip = Player->GetClass() == PlayerClass;
////    TargetComponent = NULL;
////    FOutputDeviceNull ar;
////    FString command = FString::Printf(TEXT("GetTargetComponent %p"), TargetComponent);//*TargetComponent->GetName());
////    if (PlayerShip) { Player->CallFunctionByNameWithArguments(*command, ar, this, false); }
////    Shot->Initialize(GetVelocity() + GetActorForwardVector() * ShotTravelSpeed, NULL, 0, 0, NULL, ShotCollider);
////    Shot->SetActorEnableCollision(false);
////    if (Shot) { Shot->SetTarget(Cast<USceneComponent>(Player)); }
//    if (GEngine) { GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Orange, FString::Printf(TEXT("!!!"))); }
//}




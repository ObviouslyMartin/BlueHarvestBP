// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"

// Sets default values
UProjectile::UProjectile():
//  StartSpeed(0),
//  StartVel(0),
  HomingAccel(0),
  Acceleration(0)
{
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(RootComponent);
    Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
    Collider->SetupAttachment(RootComponent);
    Driver = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Driver"));
    Driver->SetUpdatedComponent(RootComponent);
    
    Driver->ProjectileGravityScale = 0;
    Driver->bIsHomingProjectile = false;
    Driver->HomingAccelerationMagnitude = this->HomingAccel;
    
    PrimaryComponentTick.bCanEverTick = true;
    bWantsInitializeComponent = true;
    bAutoActivate = true;
    bAutoRegister = true;

    
}

UProjectile* UProjectile::SpawnFromTemplate(const FVector& StartVelocity, UProjectile* const& Template, AActor* Owner)
{

    auto NewShot = Cast<UProjectile>(Owner->CreateComponentFromTemplate(Template));
    if(NewShot)
    {
        NewShot->SetVelocity(StartVelocity);
        NewShot->SetVisibility(true);
        NewShot->SetAbsolute(true, true, false);
        NewShot->SetWorldLocation(Owner->GetActorLocation());
        NewShot->PrimaryComponentTick.bCanEverTick = true;
        NewShot->bWantsInitializeComponent = true;
        NewShot->bAutoActivate = true;
        NewShot->bAutoRegister = true;
        NewShot->Activate();
        NewShot->RegisterComponent();
        NewShot->Mesh->SetWorldLocation(NewShot->GetComponentLocation());
        NewShot->Collider->SetWorldLocation(NewShot->GetComponentLocation());
    }
    return NewShot;
}

void UProjectile::Init(const FVector& StartVelocity, USceneComponent* Target, const float& HomingAccel, const float& Acceleration, UStaticMeshComponent* Mesh, UCapsuleComponent* Collider)
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryComponentTick.bCanEverTick = true;
    
    this->HomingAccel = HomingAccel;
    this->Acceleration = Acceleration;
    if (Mesh)
    {
        this->Mesh = Mesh;
        Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false));
    }
    
    if (Collider)
    {
        this->Collider = Collider;
        Collider->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false));
        
    }
    
    Driver->ProjectileGravityScale = 0;
    Driver->Velocity = StartVelocity;
    Driver->UpdateComponentVelocity();
    Driver->bIsHomingProjectile = bool(this->HomingAccel);
    Driver->HomingAccelerationMagnitude = this->HomingAccel;
    Driver->HomingTargetComponent = Target;
}

void UProjectile::SetTarget(USceneComponent* const& Target)
{
    Driver->HomingTargetComponent = Target;
    Driver->bIsHomingProjectile = true;

}

void UProjectile::SetVelocity(const FVector& Velocity)
{
    Driver->Velocity = Velocity;
}

void UProjectile::InitRotation(const FRotator& Rotation, const bool& ResetSpeed)
{
    auto NewVel = (ResetSpeed)? Rotation.Vector() * StartSpeed : Rotation.Vector() * Driver->Velocity.Size();
    Driver->Velocity = NewVel;
}

float UProjectile::getStartSpeed() const
{
    return StartSpeed;
}

void UProjectile::SetCollisionState(ECollisionEnabled::Type EnableState) const
{
    Collider->SetCollisionEnabled(EnableState);
}

// Called when the game starts or when spawned
void UProjectile::BeginPlay()
{
    Super::BeginPlay();
    
    PrimaryComponentTick.bCanEverTick = true;
    
//    RegisterComponentWithWorld(GetWorld());
    Driver->SetUpdatedComponent(RootComponent);
    Driver->ProjectileGravityScale = 0;
    
//    if (GetOwner())
//    {
//        GetOwner()->GetWorldTimerManager().SetTimer(DebugTimer, this, &UProjectile::MessageDebug, 3);
//    }

}

void UProjectile::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (Acceleration)
    {
        Driver->Velocity += (Driver->Velocity.GetSafeNormal() * Acceleration);
        Driver->UpdateComponentVelocity();
    }
}

void UProjectile::MessageDebug() const
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Orange,
             FString::Printf
             (
              TEXT("Created: %d, Init'd: %d, Began: %d, Active: %d, Tick: %d, Location: %s, Owner/Loc: %s/%s, \nVel: %s, Visible: %d, MeshLoc: %s, ColliderLoc: %s"),
                  HasBeenCreated(),// ? TEXT("true") : TEXT("false"),
                  HasBeenInitialized(),// ? TEXT("true") : TEXT("false"),
                  HasBegunPlay(),// ? TEXT("true") : TEXT("false"),
                  IsActive(),// ? TEXT("true") : TEXT("false"),
                  IsComponentTickEnabled(),// ? TEXT("true") : TEXT("false"),
                  *GetComponentLocation().ToCompactString(),
                  GetOwner() ? *GetOwner()->GetName() : TEXT("No Owner"),
                  GetOwner() ? *GetOwner()->GetActorLocation().ToCompactString() : TEXT("_"),
              //\n
                  *Driver->Velocity.ToCompactString(),
                  IsVisible(),
                  *Mesh->GetComponentLocation().ToCompactString(),
                  *Collider->GetComponentLocation().ToCompactString()
              ));
        
    }
}


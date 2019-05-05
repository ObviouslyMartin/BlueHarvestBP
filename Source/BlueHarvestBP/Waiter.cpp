// Fill out your copyright notice in the Description page of Project Settings.

#include "Waiter.h"

// Sets default values for this component's properties
UWaiter::UWaiter() : UWaiter(0)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

UWaiter::UWaiter(float WaitTime):
Ready(true),
WaitTime(WaitTime)
{
    
}

// Called when the game starts
void UWaiter::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UWaiter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



void UWaiter::SetWaitTime(float NewWaitTime)
{
    WaitTime = NewWaitTime;
}

bool UWaiter::isReady()
{
    bool BeganReady = Ready;
    
    if(Ready && GetOwner())
    {
        GetOwner()->GetWorldTimerManager().SetTimer(Timer, this, &UWaiter::GetReady, WaitTime);
    }
    
    Ready = false;
    return BeganReady;
}

void UWaiter::GetReady()
{
    Ready = true;
}

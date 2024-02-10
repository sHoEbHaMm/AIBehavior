// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_PatrolState.h"
#include "AI_Enemy.h"

Enemy_PatrolState::Enemy_PatrolState()
{
    
}

Enemy_PatrolState::~Enemy_PatrolState()
{
}

void Enemy_PatrolState::EnterState(AAI_Enemy* enemy)
{
    UE_LOG(LogTemp, Warning, TEXT("Entering patrol"));
    //enemy->currentWaypointIndex = 0;
}

void Enemy_PatrolState::UpdateState(AAI_Enemy* enemy, float deltaTime)
{
    //UE_LOG(LogTemp, Warning, TEXT("Patroling"));

    FVector currentLocation = enemy->GetActorLocation();
    FVector targetLocation = enemy->wayPoints[enemy->currentWaypointIndex];
    FVector newLocation = FMath::VInterpConstantTo(currentLocation, targetLocation, deltaTime, 200.0f);

    enemy->SetActorLocation(newLocation);

    if (FVector::Dist(currentLocation, targetLocation) < 5.0f)
    {
        enemy->currentWaypointIndex = ((enemy->currentWaypointIndex) + 1) % enemy->wayPoints.Num();
    }
}

void Enemy_PatrolState::OnExitState(AAI_Enemy* enemy)
{
}

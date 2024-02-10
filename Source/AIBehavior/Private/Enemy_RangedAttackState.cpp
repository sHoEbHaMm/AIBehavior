// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_RangedAttackState.h"
#include "Engine/World.h"
#include "AI_Enemy.h"


Enemy_RangedAttackState::Enemy_RangedAttackState()
{
	bCanShoot = false;
}

Enemy_RangedAttackState::~Enemy_RangedAttackState()
{
}

void Enemy_RangedAttackState::EnterState(AAI_Enemy* enemy)
{
	int32 x, y;
	x = y = 1;

	orignalRotation = enemy->GetActorRotation();

	newInfo.Linkage = 0;
	newInfo.CallbackTarget = enemy;
	newInfo.ExecutionFunction = "Shoot";
	newInfo.UUID = enemy->GetUniqueID();
}

void Enemy_RangedAttackState::UpdateState(AAI_Enemy* enemy, float deltaTime)
{

	FVector targetLocation = (UGameplayStatics::GetPlayerCharacter(enemy->GetWorld(), 0))->GetActorLocation();
	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(enemy->GetActorLocation(), targetLocation);
	FVector spawnLocation(enemy->GetActorLocation().X, enemy->GetActorLocation().Y, enemy->GetActorLocation().Z + 20.0f);

	enemy->SetActorRotation(TargetRotation);

	DrawDebugLine(enemy->GetWorld(), spawnLocation, targetLocation, FColor::Cyan, false, 0.05f, 10);
}

void Enemy_RangedAttackState::OnExitState(AAI_Enemy* enemy)
{
	if (enemy->bIsRotating)
		enemy->StopRotating();
	enemy->SetActorRotation(enemy->orignalRotaion);
}

void Enemy_RangedAttackState::Shoot(AAI_Enemy* enemy)
{
	//enemy->GetWorld()->SpawnActor<AProjectile>(enemy->projectileActor, spawnLocation, enemy->GetActorRotation());
}

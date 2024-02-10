// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "AI_EnemyState.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/EngineTypes.h"
#include "Projectile.h"
#include "Engine/LatentActionManager.h"
#include "CoreMinimal.h"

/**
 * 
 */
class AAI_Enemy;
class UWorld;

class AIBEHAVIOR_API Enemy_RangedAttackState : public IEnemyState
{
public:
	virtual void EnterState(AAI_Enemy* enemy) override;
	virtual void UpdateState(AAI_Enemy* enemy, float deltaTime) override;
	virtual void OnExitState(AAI_Enemy* enemy) override;

	FRotator orignalRotation;
	bool bCanShoot;
	FLatentActionInfo newInfo;

public:
	Enemy_RangedAttackState();
	~Enemy_RangedAttackState();

	UFUNCTION()
	void Shoot(AAI_Enemy* enemy);

};

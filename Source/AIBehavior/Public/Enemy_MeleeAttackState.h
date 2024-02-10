// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "AI_EnemyState.h"
#include "CoreMinimal.h"

/**
 * 
 */
class AAI_Enemy;

class AIBEHAVIOR_API Enemy_MeleeAttackState : public IEnemyState
{
public:
	virtual void EnterState(AAI_Enemy* enemy) override;
	virtual void UpdateState(AAI_Enemy* enemy, float deltaTime) override;
	virtual void OnExitState(AAI_Enemy* enemy) override;

public:
	Enemy_MeleeAttackState();
	~Enemy_MeleeAttackState();
};

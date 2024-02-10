// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class AAI_Enemy;

class IEnemyState
{
public:
	virtual void EnterState(AAI_Enemy* enemy) {}
	virtual void UpdateState(AAI_Enemy* enemy, float deltaTime) {}
	virtual void OnExitState(AAI_Enemy* enemy) {}
};

class AIBEHAVIOR_API AI_EnemyState
{
public:
	AI_EnemyState();
	~AI_EnemyState();
};

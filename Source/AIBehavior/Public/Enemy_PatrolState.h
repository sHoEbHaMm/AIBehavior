// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "AI_EnemyState.h"
#include "CoreMinimal.h"

class AAI_Enemy;

/**
 * 
 */
class AIBEHAVIOR_API Enemy_PatrolState : public IEnemyState
{
public:
	virtual void EnterState(AAI_Enemy* enemy) override;
	virtual void UpdateState(AAI_Enemy* enemy, float deltaTime) override;
	virtual void OnExitState(AAI_Enemy* enemy) override;

private:
	FVector initialLocation;
	FVector startLocation;
	FVector endLocation;

public:
	Enemy_PatrolState();
	~Enemy_PatrolState();

};

// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_MeleeAttackState.h"
#include "AI_Enemy.h"

void Enemy_MeleeAttackState::EnterState(AAI_Enemy* enemy)
{
	enemy->StartRotating();
}

void Enemy_MeleeAttackState::UpdateState(AAI_Enemy* enemy, float deltaTime)
{
}

void Enemy_MeleeAttackState::OnExitState(AAI_Enemy* enemy)
{
	enemy->StopRotating();
}


Enemy_MeleeAttackState::Enemy_MeleeAttackState()
{
}

Enemy_MeleeAttackState::~Enemy_MeleeAttackState()
{
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "AI_Companion.h"
#include "AI_CompanionState.h"
#include "CoreMinimal.h"

class AAICompanion;
/**
 * 
 */
class AIBEHAVIOR_API Companion_FollowState : public ICompanionState
{
public:
	virtual void OnEnterState(AAICompanion* companion) override;
	virtual void UpdateState(AAICompanion* companion, float deltaTime) override;
	virtual void OnExitState(AAICompanion* companion) override;

public:
	Companion_FollowState();
	~Companion_FollowState();

private:
	ACharacter* player;
};

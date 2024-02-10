// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class AAICompanion;

/**
 * 
 */
class ICompanionState
{
public:

	virtual void OnEnterState(AAICompanion* companion) {}
	virtual void UpdateState(AAICompanion* companion, float deltaTime) {}
	virtual void OnExitState(AAICompanion* companion) {}
};

class AIBEHAVIOR_API AI_CompanionState
{
public:
	AI_CompanionState();
	~AI_CompanionState();
};

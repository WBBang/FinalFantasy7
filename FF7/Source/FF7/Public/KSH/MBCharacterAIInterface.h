// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MBCharacterAIInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMBCharacterAIInterface : public UInterface
{
	GENERATED_BODY()
};

DECLARE_DELEGATE(FAICharacterAttackFinished);
DECLARE_DELEGATE(FAICharacterShockWaveFinished);

class FF7_API IMBCharacterAIInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual float GetAIPatrolRadius() = 0;
	virtual float GetAIDetectRange() = 0;
	virtual float GetAIAttackRange() = 0;
	virtual float GetAISkillRange() = 0;
	virtual float GetAITurnSpeed() = 0;
	virtual bool GetAIGuardingSuccess() = 0;
	virtual bool GetAIGuarding() = 0;
	virtual bool GetAIDying() = 0;

	virtual void SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished) = 0;
	virtual void SetAIShockWaveDelegate(const FAICharacterShockWaveFinished& InOnShockWaveFinished) = 0;
	virtual void AttackByAI() = 0;
	virtual void ShockWaveByAI() = 0;
	virtual void GuardByAI() = 0;
	virtual void GuardSuccessByAI() = 0;
	virtual void SpeedChangeByAI(float Speed) = 0;
	virtual void DieByAI() = 0;
};

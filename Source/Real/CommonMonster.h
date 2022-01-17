// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster.h"
#include "CommonMonster.generated.h"

/**
 * 
 */
UCLASS()
class REAL_API ACommonMonster : public AMonster
{
	GENERATED_BODY()

	public:

	UFUNCTION(BlueprintCallable)
	virtual void Mfire() override;
};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletAttackPattern.h"
#include "MonsterDataTable.h"

#include "Monster.generated.h"


UCLASS(Abstract)
class REAL_API AMonster : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonster();
	
	virtual void Mfire() PURE_VIRTUAL(AMonster);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void InitMonster(const FMonsterRow* MonsterStat);
	
	UFUNCTION(BlueprintCallable)
	virtual void SetActive(bool InActive);
	//virtual void DeActive();
	
	// 공격 패턴 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackStyle")
	class UBulletAttackPattern* AttackPatternComponent;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	class UStaticMeshComponent* MonsterMeshComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Stat" )
	FMonsterRow MonsterStat;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};



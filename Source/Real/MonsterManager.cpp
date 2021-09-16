// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterManager.h"
#include "Kismet/GameplayStatics.h"
#include "MonsterDataTable.h"
#include "Components/BoxComponent.h"
#include "RealGameModeBase.h"

#include "GameFramework/Pawn.h"

// Sets default values
AMonsterManager::AMonsterManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("spawnVolume"));

	RootComponent = SpawnVolume;

	
	//ObjectPooler = CreateDefaultSubobject<UObjectPoolComponent>(TEXT("ObjectPoller"));
	//
	//데이터 테이블.
	
}

void AMonsterManager::ResetCount()
{
	NowSpawnMosterCount.eCommomMonster =0;
	NowSpawnMosterCount.eBossMonster =0;
	NowSpawnMosterCount.eTowerMonster =0;
	GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &AMonsterManager::Spawn, SpawnCooldown);
}


// Called when the game starts or when spawned
void AMonsterManager::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &AMonsterManager::Spawn, SpawnCooldown);
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();

	gm->SetMonsterManager(this);
	
}


// 스폰할수있고 없음은 너가 알아야하는거 아니냐!

void AMonsterManager::Spawn()
{
	UWorld* const World = GetWorld();
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	AMonsterActor* Monster = gm->MonsterPooler->GetPooledMonster();


	// 몬스터가 다죽었다

	// 스테이지를 늘리냐 웨비를 늘리냐 체크한다
	// 몬스터가 잘 소환됐는지 확인한다.

	// 소환해야할때 이걸 키고 해야할때 = 스테이지로 넘어갈때!
	// 다되면 꺼지는데

	// 목표만큼 
	if(NowSpawnMosterCount.eCommomMonster < gm->GetGoalCommonMonsterCount())
	{
		
		if (Monster == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Cannot spawn"));
			GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &AMonsterManager::Spawn, SpawnCooldown, false);
			return;
		}
		// 스폰 위치
		Monster->SetActorLocation(SpawnLocation[0]);
		//몬스터 종류
		Monster->InitMonster(1);
		// 활성화 ㄱㄱ
		Monster->SetActive(true);
		UE_LOG(LogTemp, Warning, TEXT("Monster spawn"));
		//목표수치 ++
		NowSpawnMosterCount.eCommomMonster++;
		GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &AMonsterManager::Spawn, SpawnCooldown);
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::FromInt(NowSpawnMosterCount.eCommomMonster));
	}
	else
	{
		//꺼버린다.
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("PULL"));
	
	}


		

}

// Called every frame
void AMonsterManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

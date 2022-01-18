// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


#include "BulletPoolComopnent.h"
#include "ObjectPoolComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
//#include "PlayerSkillDataTable.h"
#include "ItemPoolComponent.h"
#include "GameStateDataTable.h"
#include "MonsterDataTable.h"
#include "DataTableList.h"
#include "Particles/ParticleSystem.h"
#include "StageManageComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MonsterDataTable.h"
#include "UObject/ConstructorHelpers.h"
#include "MainPawn.h"
#include "PlayerSaveGame.h"
#include "BossMonsterActor.h"
#include "ItemActor.h"
#include "ChooseSkillWidget.h"

#include "GameStateDataTable.h"
#include "MonsterManager.h"
#include "RealGameModeBase.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class ARealGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,Category="Spawner")
	bool trigger;

	void MonsterSpawn();
	
	//타이머 핸들
	FTimerHandle MonsterSpawnTimer;
	// 메인으로 돌아가기 핸들
	FTimerHandle ReturnToTitleTimerHandle;

	
	//
	// class UDataTable* MonsterData;
	// class UDataTable* PlayerSkillData;
	// class UDataTable* GameStageData;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AMonsterManager> SDataTableManager;

	UPROPERTY(EditAnywhere)
	class UDataTable*  DataTableManageClass;
	

	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AMonsterManager> SDataTableManage;

	class AMonsterManager* WorldMonsterManger;

	FWaveType NowMosterCount; 
	 
	// FWaveType WaveMonsterCount;
	//float StartTime =0.0f;

protected:

	
public:
	ARealGameModeBase();
	virtual void BeginPlay() override;
	// 몬스터 매니저에게 일시키기
	void SetMonsterManager(AMonsterManager* mMonsterManager);

	// 스테이지 통과인지 검사
	void CheckStage();
	
	//메쉬

	UPROPERTY(EditAnywhere)
	class UDataTable*  CommonMonsterDataTable;

	// 스마트포인터 사용???
	UPROPERTY(BlueprintReadOnly)
	FDataTableManage DataTableManager;

	
	FCommonMonsterData* GetCommonMonsterData(int Num=1); 

	
	// 몬스터 수를 줄여 웨이브 관리
	void DecreaseCommomMonsterCount();
	
	void DecreaseTowerMonsterCount();
	
	void DecreaseBossMonsterCount();
	
	virtual void Tick(float DeltaTime) override;

	void ReturnToTitle();
	
	
	
	int NowStage = 1;
	int NowWave	= 1;
	
	// 몬스터 생성 주기
	UPROPERTY(EditAnywhere,Category="Spawner")
	float MonsterSpawnCoolTime =2.0f;

	UPROPERTY(EditAnywhere,Category="Spawner")
	int MonsterSpawnNum =2;

	UPROPERTY(EditAnywhere,Category="Spawner")
	int MonsterType =2;


	//총알 담기
	UPROPERTY(EditAnywhere,Category="Spawner")
		class 	UBulletPoolComopnent* BulletPooler;

	// 몬스터 담기 
	UPROPERTY(EditAnywhere,Category="Spawner")
		class UObjectPoolComponent* MonsterPooler;

	UPROPERTY(EditAnywhere,Category="Spawner")
		class UItemPoolComponent* ItemPooler;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Spawner")
		class UStageManageComponent* StageManageComponent;


	//
	// //몬스터 데이터 초기화
	// FMonsterRow* GetMonsterRowData(int rowN);
	// FMonsterRow* GetMonsterRowData(FName mSkillName);
	//
	// //플레이어 스킬 가져오기
	// FPlayerSkillRow* GetPlayerSkillRowDataToNum(int rowN);
	// FPlayerSkillRow* GetPlayerSkillRowDataToNum(FName mSkillName);
	//
	// //스테이지 정보 가져오기
	// FGameStateRow* GetGameStateRowData(int rowN);

	//클릭효과음
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* ClickSound;

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* StatUpSound;

	//몬스터 죽는 효과음
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* MonsterDeadSound;

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* MonsterHitSound;

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* GameClearSound;

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* LoseSound;

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* LoseSound2;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	class UParticleSystem* HitedParticle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	class UParticleSystem* DeadParticle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	class UParticleSystem* DeadParticle2;

	// // 플레이어 오른쪽아래 위젯
	// UPROPERTY(EditAnywhere)
	// TSubclassOf<UUserWidget> PlayerRightWidgetClass;
	//
	// // 플레이어 오른쪽아래 위젯
	// UPROPERTY(VisibleInstanceOnly)
	// class URightWidget* PlayerRightWidget;

	// 플레이어 스킬선택
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> PlayerSkillChooseClass;

	// 플레이어 스킬선택 위젯
	UPROPERTY(VisibleInstanceOnly)
	class UChooseSkillWidget* PlayerSkillChooseWidget;

	//FORCEINLINE	float GetPlayTime() const {return StartTime;};

	//게임저장
	UFUNCTION(BlueprintCallable)
	void Save();

	//게임 불러오기
	UFUNCTION(BlueprintCallable)
	void Load();

	// 몇마리 잡아야하는지 가져오기
	int GetGoalCommonMonsterCount();
	int GetGoalTowerMonsterCount();
	int GetGoalBossMonsterCount();
	int GetGoalWave();


	void SetNowStage(int mStage);

};
	



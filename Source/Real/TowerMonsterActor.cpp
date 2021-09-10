// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerMonsterActor.h"


ATowerMonsterActor::ATowerMonsterActor()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Mesh/TowerRabbit.TowerRabbit"));
	MonsterMeshComponent->SetStaticMesh(MeshAsset.Object);
	AttackCount = 0;
	FireRate = 2.0f;
}



void ATowerMonsterActor::Tick(float DeltaTime)
{
	//Super::Tick(DeltaTime);

	if (Active && !isStun)
	{
		AActor* player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		FRotator newrot = (player->GetActorLocation() - GetActorLocation()).Rotation();
		newrot.Pitch = 0.f;
		newrot.Roll = 0.f;

		SetActorRotation(newrot);

		FireShot();
	}
}


void ATowerMonsterActor::FireShot()
{
	if (bCanFire)
	{
		BossBulletPattern = 0; //FMath::RandRange(0, 4);
	
		switch (BossBulletPattern)
		{
		case 0:
			// 0.3�� �� 5��
			FireCircleShot();
			break;
			
		default:
			break;
		}
		bCanFire = false; // ����

	}
}

void ATowerMonsterActor::FireCircleShot()
{
	UWorld* const World = GetWorld();
	
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	ABullet* monsterBullet = gm->BulletPooler->GetPooledBullet();
	
	if (monsterBullet && World)
	{
		
		for (int i = 0; i < 36; i++)
		{
			monsterBullet = gm->BulletPooler->GetPooledBullet();
			// ���� ��ġ
			FVector Location = GetActorLocation();
			// �� (x,y)
			FVector Circledir(cos((2 * PI * i) / 36), sin((2 * PI * i) / 36), 0.f);
			// �������� 100�� ��(x,y)
			Circledir *= 100;
			// ����ġ�� �� ��ġ�� ���ؼ�
			Location += Circledir;
			// ������ ����ġ - ����ġ
			FVector Dir = Location - GetActorLocation();
			// ���⺤�� 
			Dir.Normalize();

			const FVector FMovement = Dir * BulletSpeed; //
			// �������ִ� ���� ����?
			monsterBullet->SetOwnerActor(this);
			// �������ִ� �Ѿ���ġ
			monsterBullet->SetActorLocation(Location);

			//�Ѿ� �ӵ�
			monsterBullet->SetVelocity(FMovement);
			// �˾Ƽ� ��������ϰ�
			monsterBullet->SetLifeSpan();
			// Ȱ��ȭ��Ų��.
			monsterBullet->SetActive(true);

		}
		if(AttackCount<2)
		{
			
			AttackCount++;
			World->GetTimerManager().SetTimer(AttackTimer, this, &ATowerMonsterActor::FireCircleShot, 0.5f);
		}
		else
		{
		
			AttackCount=0;
			World->GetTimerManager().SetTimer(AttackTimer, this, &AMonsterActor::ShotTimerExpired, FireRate);	
		}
		
	}
}
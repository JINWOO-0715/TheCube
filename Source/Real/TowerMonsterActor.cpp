// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerMonsterActor.h"
#include "CoinItem.h"

float ATowerMonsterActor::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = DamageAmount;//Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	MonsterHP -= Damage;
	ChangeHitedMTTimer();
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();

	if (MonsterHP < 0.f)
	{
		UGameplayStatics::PlaySound2D(this, gm->MonsterDeadSound );
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), gm->DeadParticle, GetActorLocation(),FRotator(0.f,0.f,0.f),FVector(3.f,3.f,3.f));

		AMainPawn* player=Cast<AMainPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		player->PlayerScoreWidget->DereaseMonsterText();
		
		int rand = FMath::RandRange(0, 1);
		
		if (rand == 0)
		{
			
			AItemActor* Item = gm->ItemPooler->GetPooledUItem();
			Item->SetActorLocation(GetActorLocation());
			Item->SetActive(true);
		}
		
		rand = FMath::RandRange(0, 1);
		
		if (rand == 0)
		{
			
			ACoinItem* Coin = gm->ItemPooler->GetPooledCoinItem();
			Coin->SetActorLocation(GetActorLocation()+FVector(50.f,0.f,0.f));
			Coin->SetActive(true);
		}
		// 경치구슬 획득 확률 40%
		Deactivate();
		gm->DecreaseTowerMonsterCount();
	}
	else
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), gm->HitedParticle, GetActorLocation(),FRotator(0.f,0.f,0.f),FVector(3.f,3.f,3.f));
		UGameplayStatics::PlaySound2D(this, gm->MonsterHitSound);
	}
	return Damage;	
}
ATowerMonsterActor::ATowerMonsterActor()
{
	// static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Mesh/TowerRabbit.TowerRabbit"));
	// MonsterMeshComponent->SetStaticMesh(MeshAsset.Object);
	// AttackCount = 0;
	// FireRate = 2.0f;
	Imoge->SetRelativeLocation(FVector(0.f,0.f,600.f));
	
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
			// 0.3초 총 5번
			FireCircleShot();
			break;
			
		default:
			break;
		}
		bCanFire = false; // 끊고

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
			// 몬스터 위치
			FVector Location = GetActorLocation();
			// 원 (x,y)
			FVector Circledir(cos((2 * PI * i) / 36), sin((2 * PI * i) / 36), 0.f);
			// 반지름이 100인 원(x,y)
			Circledir *= 100;
			// 내위치에 그 위치를 더해서
			Location += Circledir;
			// 방향은 먼위치 - 내위치
			FVector Dir = Location - GetActorLocation();
			// 방향벡터 
			Dir.Normalize();

			const FVector FMovement = Dir * BulletSpeed; //
			// 가지고있는 액터 누구?
			monsterBullet->SetOwnerActor(this);
			// 가지고있는 총알위치
			monsterBullet->SetActorLocation(Location);

			//총알 속도
			monsterBullet->SetVelocity(FMovement);
			// 알아서 살아지게하고
			monsterBullet->SetLifeSpan(	BulletLifeSpan);
			// 활성화시킨다.
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

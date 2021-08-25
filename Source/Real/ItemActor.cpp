// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemActor.h"
#include "MainPawn.h"
// Sets default values
AItemActor::AItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BulletMeshAsset(TEXT("/Game/Mesh/Box.Box"));

	// Create mesh component for the projectile sphere
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetStaticMesh(BulletMeshAsset.Object);
	ItemMesh->SetupAttachment(RootComponent);
	ItemMesh->SetGenerateOverlapEvents(false);
	ItemMesh->OnComponentHit.AddDynamic(this, &AItemActor::OnHit);
	ItemMesh->SetNotifyRigidBodyCollision(true);
}

// Called when the game starts or when spawned
void AItemActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("COllision BoxItem"));
		AMainPawn* Player = Cast<AMainPawn>(OtherActor);
		Player->GetExperience(UPExp);
		//Player.add
		Destroy();
	}
	
}
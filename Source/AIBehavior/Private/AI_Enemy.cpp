// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Enemy.h"
#include "Enemy_PatrolState.h"
#include "Enemy_MeleeAttackState.h"
#include "Enemy_RangedAttackState.h"
#include "Components/InterpToMovementComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AAI_Enemy::AAI_Enemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	eyesStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EyesStaticMesh"));
	bodyStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	lowerBodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LowerBody"));
	handsStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hands"));

	rotatatingMovementComp = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingComp"));
	rotatatingMovementComp->bAutoActivate = false;

	eyesStaticMesh->SetupAttachment(staticMesh);
	bodyStaticMesh->SetupAttachment(staticMesh);
	lowerBodyMesh->SetupAttachment(bodyStaticMesh);
	handsStaticMesh->SetupAttachment(bodyStaticMesh);

	RootComponent = staticMesh;
	eyesStaticMesh->SetupAttachment(RootComponent);

	staticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	eyesStaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	longRangeRadius = CreateDefaultSubobject<UCapsuleComponent>(TEXT("longRangeRadius"));
	longRangeRadius->SetupAttachment(RootComponent);
	meleeRangeRadius = CreateDefaultSubobject<UCapsuleComponent>(TEXT("meleeRangeRadius"));
	meleeRangeRadius->SetupAttachment(RootComponent);
	longRangeRadius->SetGenerateOverlapEvents(true);
	meleeRangeRadius->SetGenerateOverlapEvents(true);

	//Initializations
	longRangeRadius->SetCapsuleRadius(500.0f, true);
	meleeRangeRadius->SetCapsuleRadius(250.0f, true);
	longRangeRadius->ShapeColor = FColor::Blue;
	meleeRangeRadius->ShapeColor = FColor::Magenta;

	longRangeRadius->OnComponentBeginOverlap.AddDynamic(this, &AAI_Enemy::BeginOverlapWithLongRangeRadius);
	longRangeRadius->OnComponentEndOverlap.AddDynamic(this, &AAI_Enemy::EndOverlapWithLongRangeRadius);
	meleeRangeRadius->OnComponentBeginOverlap.AddDynamic(this, &AAI_Enemy::BeginOverlapWithMeleeRangeRadius);
	meleeRangeRadius->OnComponentEndOverlap.AddDynamic(this, &AAI_Enemy::EndOverlapWithMeleeRangeRadius);

	currentState = new Enemy_PatrolState();
	currentState->EnterState(this);

	bisInLongRangeRadius = false;
	bisInMeleeRangeRadius = false;
	bIsRotating = false;

	orignalRotaion = GetActorRotation();
}

// Called when the game starts or when spawned
void AAI_Enemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAI_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (currentState)
	{
		currentState->UpdateState(this, DeltaTime);
	}
}

void AAI_Enemy::BeginOverlapWithLongRangeRadius(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	
	if (player == (ACharacter*)OtherActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player is overlapping(long range)"));
		Enemy_RangedAttackState* RangedAttackState = new Enemy_RangedAttackState();
		this->SetState(RangedAttackState);
		bisInLongRangeRadius = true;
	}
}

void AAI_Enemy::EndOverlapWithLongRangeRadius(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (player == (ACharacter*)OtherActor)
	{
		bisInLongRangeRadius = false;
		UE_LOG(LogTemp, Warning, TEXT("Player is not overlapping (long range)"));
		Enemy_PatrolState* patrolState = new Enemy_PatrolState();
		this->SetState(patrolState);
	}
}

void AAI_Enemy::SetState(IEnemyState* newState)
{
	if (currentState)
	{
		currentState->OnExitState(this);
		delete currentState;
	}
	currentState = newState;
	currentState->EnterState(this);
}

void AAI_Enemy::BeginOverlapWithMeleeRangeRadius(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (player == (ACharacter*)OtherActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player is overlapping (small range)"));
		Enemy_MeleeAttackState* meleeAttackState = new Enemy_MeleeAttackState();
		this->SetState(meleeAttackState);
		bisInMeleeRangeRadius = true;
	}
}

void AAI_Enemy::EndOverlapWithMeleeRangeRadius(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (player == (ACharacter*)OtherActor)
	{
		bisInLongRangeRadius = false;
		UE_LOG(LogTemp, Warning, TEXT("Player is not overlapping (short range)"));
		Enemy_RangedAttackState* RangedAttackState = new Enemy_RangedAttackState();
		this->SetState(RangedAttackState);
		bisInMeleeRangeRadius = false;
	}
}

void AAI_Enemy::StartRotating()
{
	this->rotatatingMovementComp->Activate(true);
	this->bIsRotating = true;
}

void AAI_Enemy::StopRotating()
{
	this->rotatatingMovementComp->Deactivate();
	this->bIsRotating = false;
}



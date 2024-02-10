// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AI_EnemyState.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include"Projectile.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "AI_Enemy.generated.h"


UCLASS()
class AIBEHAVIOR_API AAI_Enemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAI_Enemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* staticMesh;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* eyesStaticMesh;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* bodyStaticMesh;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* handsStaticMesh;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* lowerBodyMesh;

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* longRangeRadius;

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* meleeRangeRadius;

	UPROPERTY(VisibleAnywhere)
	class URotatingMovementComponent* rotatatingMovementComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pathing", meta = (ExposeOnSpawn = "true", MakeEditWidget = "true"))
	TArray<FVector> wayPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileShooting", meta = (ExposeOnSpawn = "true", MakeEditWidget = "true"))
	TSubclassOf<class AProjectile> projectileActor;

	UFUNCTION()
	void BeginOverlapWithLongRangeRadius(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlapWithLongRangeRadius(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	UFUNCTION()
	void BeginOverlapWithMeleeRangeRadius(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlapWithMeleeRangeRadius(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	void SetState(IEnemyState* newState);

	int currentWaypointIndex;

	bool bisInLongRangeRadius, bisInMeleeRangeRadius;

	void StartRotating();
	void StopRotating();
	bool bIsRotating;

	FRotator orignalRotaion;

private:
	IEnemyState* currentState;
};

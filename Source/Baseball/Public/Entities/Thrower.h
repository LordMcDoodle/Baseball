#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Thrower.generated.h"

class ABall;
class AGameplayManager;

UCLASS()
class BASEBALL_API AThrower : public AActor
{
	GENERATED_BODY()
	
public:	
	AThrower();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	//Properties
	float ThrowForce;

	ABall* ThrowBall();

	//Getter and Setter
	void SetGameplayManager(AGameplayManager* value) { GM = value; }
	AGameplayManager* SetGameplayManager() { return GM; }

protected:
	virtual void BeginPlay() override;
	
	/*
	Components
	*/

	UPROPERTY(EditAnywhere)
	UClass* ThrowerFieldSystemClass;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* mesh;

	UPROPERTY(VisibleAnywhere)
	AGameplayManager* GM;

	/*
	Functions
	*/

	void CreateField();

	/*
	Temporary
	*/

	UPROPERTY(EditAnywhere)
	UClass* BallClass;
	FTimerHandle ThrowTimer;
};

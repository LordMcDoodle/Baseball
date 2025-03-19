#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Thrower.generated.h"

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


	void ThrowBall();
protected:
	virtual void BeginPlay() override;
	
	/*
	Components
	*/

	UPROPERTY(EditAnywhere)
	UClass* ThrowerFieldSystemClass;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* mesh;

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

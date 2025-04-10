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

	void PlayMontage();

	void Pitch();

	UPROPERTY(VisibleAnywhere)
	//Properties
	float ThrowForce;

	UPROPERTY(EditInstanceOnly)
	ABall* BallInHand;

	//Getter and Setter
	void SetGameplayManager(AGameplayManager* value) { GM = value; }
	AGameplayManager* SetGameplayManager() { return GM; }

protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void ThrowBall();


	/*
	Components
	*/

	UPROPERTY(EditAnywhere)
	UClass* ThrowerFieldSystemClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* mesh;

	UPROPERTY(VisibleAnywhere)
	AGameplayManager* GM;

	UPROPERTY(EditInstanceOnly)
	AActor* ThrowTarget;

	//Montages
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* Montage;

	UAnimInstance* AnimInstance;

	//Temporary

	void SpawnNewBall();
	UPROPERTY(EditAnywhere)
	UClass* BallClass;

	UFUNCTION()
	void ApplyImpulse();

};

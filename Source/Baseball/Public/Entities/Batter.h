
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Batter.generated.h"

class ABall;
class UAnimInstance;
class UBoxComponent;
class ABat;
class AGameplayManager;

UCLASS()
class BASEBALL_API ABatter : public APawn
{
	GENERATED_BODY()
	
public:	
	//Inherited
	ABatter();

	virtual void Tick(float DeltaTime) override;

	//Components
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* mesh;

	//Functions
	void SwingBat();
	void MoveBat(FVector MovementVector);
	void PlayMontage();
	void HitBall(ABall* ball);


	UPROPERTY(VisibleAnywhere)
	float SwingForce;

	AActor* TargetToHit = nullptr;

	//Getter and Setter
	void SetGameplayManager(AGameplayManager* value) { GM = value; }
	AGameplayManager* SetGameplayManager() { return GM; }

protected:

	//Inherited
	virtual void BeginPlay() override;

	//Components
	UPROPERTY(EditAnywhere)
	UClass* BatterFieldSystemClass;
	UPROPERTY(EditAnywhere)
	ABat* bat;
	UPROPERTY(VisibleAnywhere)
	AGameplayManager* GM;


	//Montages
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* Montage;

	UAnimInstance* AnimInstance;

	//Variables
	float LocationYMax;
	float LocationYMin;
	float LocationZMax;
	float LocationZMin;

};

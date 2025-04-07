
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Batter.generated.h"

class ABall;
class UAnimInstance;
class UBoxComponent;
class ABat;

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
	void SwingBat(FVector BatToTargetVector, ABall* ball = nullptr);
	void MoveBat(FVector MovementVector);
	void PlayMontage();

	UPROPERTY(VisibleAnywhere)
	float SwingForce;



protected:

	//Inherited
	virtual void BeginPlay() override;

	//Components
	UPROPERTY(EditAnywhere)
	UClass* BatterFieldSystemClass;
	UPROPERTY(EditAnywhere)
	ABat* bat;

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

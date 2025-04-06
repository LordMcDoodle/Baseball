
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Batter.generated.h"

class ABall;
class UAnimInstance;
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

	UPROPERTY(VisibleAnywhere)
	float SwingForce;
	void PlayMontage();
protected:

	//Inherited
	virtual void BeginPlay() override;

	//Components
	UPROPERTY(EditAnywhere)
	UClass* BatterFieldSystemClass;

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


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Batter.generated.h"

class ABall;
class UAnimInstance;
UCLASS()
class BASEBALL_API ABatter : public AActor
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
	void SwingBat(FVector BatToTargetVector, ABall* ball);

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

	//Functions
	void CreateFields();



};

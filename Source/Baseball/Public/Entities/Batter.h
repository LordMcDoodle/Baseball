
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Batter.generated.h"

UCLASS()
class BASEBALL_API ABatter : public AActor
{
	GENERATED_BODY()
	
public:	
	//Inherited
	ABatter();

	virtual void Tick(float DeltaTime) override;

	//Functions
	void SwingBat();


protected:

	//Inherited
	virtual void BeginPlay() override;

	//Components
	UPROPERTY(EditAnywhere)
	UClass* BatterFieldSystemClass;

	//Variables
	UPROPERTY(EditAnywhere)
	float MaxHitForce = 100000.f;
	UPROPERTY(EditAnywhere)
	float MinHitForce = 1000.f;

	//Functions
	void CreateFields();



};

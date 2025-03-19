
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

	UPROPERTY(VisibleAnywhere)
	float SwingForce;

protected:

	//Inherited
	virtual void BeginPlay() override;

	//Components
	UPROPERTY(EditAnywhere)
	UClass* BatterFieldSystemClass;

	//Functions
	void CreateFields();



};


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

class UCapsuleComponent;

UCLASS()
class BASEBALL_API ABall : public AActor
{
	GENERATED_BODY()
	
public:	
	ABall();
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* mesh;
	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* capsule;

};

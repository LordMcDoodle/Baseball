
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

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* mesh;
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* capsule;

};

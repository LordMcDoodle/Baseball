
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

class UCapsuleComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class BASEBALL_API ABall : public AActor
{
	GENERATED_BODY()
	
public:	
	ABall();
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* mesh;
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* FollowCamera;
	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SpringArm;

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* capsule;

};

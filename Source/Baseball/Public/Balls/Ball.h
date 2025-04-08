
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

class UCapsuleComponent;
class UCameraComponent;
class USpringArmComponent;
class AGameplayManager;

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

	bool BallAlreadyHitTarget = false;
	bool BallHasBeenSent = false;

	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//Getter/Setters
	void SetGameplayManager(AGameplayManager* value) { GM = value; }


protected:

	virtual void BeginPlay() override;

	UPROPERTY()
	AGameplayManager* GM = nullptr;

};

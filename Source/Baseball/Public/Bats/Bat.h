
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bat.generated.h"

class UBoxComponent;

UCLASS()
class BASEBALL_API ABat : public AActor
{
	GENERATED_BODY()
	
public:	

	ABat();

	virtual void Tick(float DeltaTime) override;

	void Equip(USceneComponent* InParent, FName InSocketName, AActor* NewOwner, APawn* NewInstigator);

	void AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName);

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	//Components
	UStaticMeshComponent* mesh;


	//Hitboxes and Traces
	UPROPERTY(VisibleAnywhere, Category = HitBoxes)
	UBoxComponent* SweetSpotBox;
	UPROPERTY(VisibleAnywhere, Category = HitBoxes)
	UBoxComponent* WonkyBox;
	UPROPERTY(VisibleAnywhere, Category = HitBoxes)
	UBoxComponent* SlowBox;

	UPROPERTY(VisibleAnywhere, Category = HitBoxes)
	USceneComponent* SweetSpotTraceStart;
	UPROPERTY(VisibleAnywhere, Category = HitBoxes)
	USceneComponent* SweetSpotTraceEnd;
	UPROPERTY(VisibleAnywhere, Category = HitBoxes)
	USceneComponent* WonkyBoxTraceStart;
	UPROPERTY(VisibleAnywhere, Category = HitBoxes)
	USceneComponent* WonkyBoxTraceEnd;
	UPROPERTY(VisibleAnywhere, Category = HitBoxes)
	USceneComponent* SlowBoxTraceStart;
	UPROPERTY(VisibleAnywhere, Category = HitBoxes)
	USceneComponent* SlowBoxTraceEnd;

};

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicPad.generated.h"

UCLASS()
class BASEBALL_API ABasicPad : public AActor
{
	GENERATED_BODY()
	
public:	
	ABasicPad();
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* mesh;

protected:
	virtual void BeginPlay() override;


};

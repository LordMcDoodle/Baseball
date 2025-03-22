
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetWidget.generated.h"

UCLASS()
class BASEBALL_API ATargetWidget : public AActor
{
	GENERATED_BODY()
	
public:	
	ATargetWidget();

	virtual void Tick(float DeltaTime) override;

	//Components
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* mesh;

protected:
	virtual void BeginPlay() override;

};

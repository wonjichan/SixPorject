#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingActor.generated.h"

UCLASS()
class SIXPROJECT_API ARotatingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ARotatingActor();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly , Category = "Scene/Root")
	USceneComponent* SceneRoot; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene/Properties")
	UStaticMeshComponent* StaticMeshComp; 

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Variable/Properties")
	float RotationSpeed; 

	FTimerHandle RotateTimerHandle;
public:	
	virtual void Tick(float DeltaTime) override;
	void DestroyActor();
};

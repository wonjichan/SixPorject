// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoveActor.generated.h"


UCLASS()
class SIXPROJECT_API AMoveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMoveActor();

private:
	bool IsMovingForward; 
	FTimerHandle RotateTimerHandle;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scene/Root")
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene/Properties")
	UStaticMeshComponent* StaticMeshComp;

	//시작 위치 
	UPROPERTY(BlueprintReadOnly, Category = "Variable/Properties")
	FVector StartLocation;

	//매 프레임마다 체크 할 엑터의 현재 위치 
	UPROPERTY(BlueprintReadOnly, Category = "Variable/Properties")
	FVector CurrentLocation;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Variable/Properties")
	float MoveSpeed;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Variable/Properties")
	float MaxRange;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void MovingActor();
};

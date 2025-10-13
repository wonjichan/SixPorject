#include "RotatingActor.h"
#include "TimerManager.h"

ARotatingActor::ARotatingActor()
{
	PrimaryActorTick.bCanEverTick = true;
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot")); 
	SetRootComponent(SceneRoot); 

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	RotationSpeed = 100.0f; 
}

void ARotatingActor::BeginPlay()
{
	Super::BeginPlay();

	float RandomTimer = FMath::RandRange(10.0f, 20.0f);

	GetWorld()->GetTimerManager().SetTimer(RotateTimerHandle, this, &ARotatingActor::DestroyActor, RandomTimer, false);
}

void ARotatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		AddActorLocalRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));
	}
	//Local 좌표계 기준
	////World 좌표계 기준 
	//월드의 절대 좌표로 즉시 이동시키는 함수 b
	//SetActorLocation(FVector(0.0f, StartLocation.Y += (MoveSpeed * DeltaTime), 0.0f));
}

void ARotatingActor::DestroyActor()
{
	UWorld* World = GetWorld();
	if (!World) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = nullptr;
	SpawnParams.Instigator = GetInstigator();

	float RandomLocate = FMath::RandRange(-500.0f, 500.0f);
	float RandomRotationSpeed = FMath::RandRange(150.0f, 300.0f);

	FVector NewLocation = GetActorLocation() + FVector(RandomLocate, 0.0f, 0.0f);
	FRotator NewRotation = GetActorRotation();

	ARotatingActor* NewActor = World->SpawnActor<ARotatingActor>(GetClass(), NewLocation, NewRotation, SpawnParams);
	if (NewActor)
	{
		NewActor->RotationSpeed = RandomRotationSpeed;
	}
	Destroy(); 
}

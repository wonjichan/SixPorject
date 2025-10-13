#include "MoveActor.h"
#include "RotatingActor.h"
#include "EngineUtils.h"

// Sets default values
AMoveActor::AMoveActor()
{
	PrimaryActorTick.bCanEverTick = true;
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot")); 
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	MoveSpeed = 300.0f;
	IsMovingForward = false;
}

void AMoveActor::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
	if (MaxRange <= 0)
	{
		MaxRange = 500.0f;
	}

	float RandomTimer = FMath::RandRange(10.0f, 20.0f);
	GetWorld()->GetTimerManager().SetTimer(RotateTimerHandle, this, &AMoveActor::MovingActor, RandomTimer, false);
}

void AMoveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentLocation = GetActorLocation();
	FVector UpdateMove;
	if (!FMath::IsNearlyZero(MoveSpeed))
	{
		//�ǵ��ư��� ���� 
		//IsMovingForward(������ �̵� ���� ����) = true 
		//�ִ� ���� MaxRange ���� ũ�ų� ���� �� 
		//������ ������ �̵��ϴ� ���� = false 
		if (IsMovingForward && CurrentLocation.Y >= StartLocation.Y + MaxRange)
		{
			IsMovingForward = false;
		}
		//������ �̵� ���� 
		//IsMovingForward(������ �̵� ���� ����) = false 
		//���� ��ġ StartLocation.Y ���� �۰ų� ���� �� 
		//������ ������ �̵��ϴ� ���� = true 
		else if(!IsMovingForward && CurrentLocation.Y <= StartLocation.Y)
		{
			IsMovingForward = true; 
		}
		float Direction = IsMovingForward ? 1.0f : -1.0f;
		UpdateMove = { 0.0f, Direction * MoveSpeed * DeltaTime, 0.0f };
		AddActorLocalOffset(UpdateMove);
	}
}
void AMoveActor::MovingActor()
{
	UWorld* World = GetWorld(); 
	if (!World) return; 
	
	float RandomLocate = FMath::RandRange(-600.0f, 600.0f);
	float RandomMoveSpeed = FMath::RandRange(200.0f, 500.0f);
	
	FRotator NewRotation = GetActorRotation();

	FVector NewLocation = GetActorLocation() + FVector(RandomLocate, 0.0f, 0.0f);
	
	FActorSpawnParameters SpawnParams; 
	SpawnParams.Owner = nullptr; 
	SpawnParams.Instigator = GetInstigator(); 

	AMoveActor* NewActor = World->SpawnActor<AMoveActor>(GetClass(), NewLocation, NewRotation, SpawnParams);

	if (NewActor)
	{
		NewActor->MoveSpeed = RandomMoveSpeed;
	}
	Destroy();
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipController.h"
#include "BulletController.h"
#include "EnemyController.h"
#include "SpaceShooterGameMode.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AShipController::AShipController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Set CollisionBox in BP with Overlap Event
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	CollisionBox->SetGenerateOverlapEvents(true);
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AShipController::OnTriggerEnter);

	//Receive Input from Player 0 (set in Project Settings)
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AShipController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AShipController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CurrentVelocity.IsZero()) 
	{
		FVector NewLocation = GetActorLocation() + (Speed * CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}
}

// Called to bind functionality to input (set in Project Settings) 
void AShipController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveX", this, &AShipController::Move_XAxis);
	InputComponent->BindAxis("MoveY", this, &AShipController::Move_YAxis);
	InputComponent->BindAction("Shoot",IE_Pressed, this, &AShipController::OnShoot);
	InputComponent->BindAction("Restart", IE_Pressed, this, &AShipController::OnRestart).bExecuteWhenPaused = true;
}

// Move X Axis 
void AShipController::Move_XAxis(float AxisValue)
{
	CurrentVelocity.X = AxisValue * 30.0f;

}

// Move Y Axis
void AShipController::Move_YAxis(float AxisValue)
{
	CurrentVelocity.Y = AxisValue * 30.0f;
}

// Shoot Func
void AShipController::OnShoot() 
{
	UWorld* World = GetWorld();
	
	if (World) //Null-Safety
	{
		FVector Location = GetActorLocation();	// Get the Current Actor Location 

		World->SpawnActor<ABulletController>(BulletBP, Location, FRotator::ZeroRotator); //Spawn Bullet
	}
}

// Restart Func
void AShipController::OnRestart() 
{
	if (Died) 
	{
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName(), false));
	}
}

// Game Over Func 
void AShipController::OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComponent, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	if(OtherActor->IsA(AEnemyController::StaticClass())) 
	{
		Died = true;
		this->SetActorHiddenInGame(true);

		((ASpaceShooterGameMode*)GetWorld()->GetAuthGameMode())->OnGameOver();

		//The game is paused
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}




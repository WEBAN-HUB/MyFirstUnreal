﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"
#include "FPSProjectile.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 일인칭 카메라 컴포넌트를 생성합니다.
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));

	// 카메라 컴포넌트를 캡슐 컴포넌트에 붙입니다.
	FPSCameraComponent->SetupAttachment(GetCapsuleComponent());

	// 카메라 위치를 눈 살짝 위쪽으로 잡습니다.
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));

	// 폰의 카메라 로테이션 제어를 허용합니다.
	FPSCameraComponent->bUsePawnControlRotation = true;



	// 일인칭 메시 컴포넌트입니다.
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));

	// 소유 플레이어만 이 메시를 볼 수 있습니다.
	FPSMesh->SetOnlyOwnerSee(true);

	// FPS 메시를 FPS 카메라에 붙입니다.
	FPSMesh->SetupAttachment(FPSCameraComponent);

	// 일부 환경 섀도잉을 꺼 메시가 하나인 듯 보이는 느낌을 유지합니다.
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	// 자신 이외 모두가 일반 몸통 메시를 볼 수 있습니다.
	GetMesh()->SetOwnerNoSee(true);

}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (GEngine)
	{
		// 5 초간 디버그 메시지를 표시합니다. (첫 인수인) -1 "Key" 값은 이 메시지를 업데이트 또는 새로고칠 필요가 없음을 나타냅니다.
 
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter"));
	}

}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	// "movement" 바인딩 구성

	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);

	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	// "Look" 바인딩 구성

	PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);

	// "action" 바인딩을 구성합니다.
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);

	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::StopJump);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);

}


void AFPSCharacter::MoveForward(float value)
{
	// 어느 쪽이 전방인지 알아내어, 플레이어가 그 방향으로 이동하고자 한다고 기록합니다.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);

	AddMovementInput(Direction, value);

}


void AFPSCharacter::MoveRight(float value)
{
	// 어느 쪽이 전방인지 알아내어, 플레이어가 그 방향으로 이동하고자 한다고 기록합니다.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	
	AddMovementInput(Direction, value);

}


void AFPSCharacter::StartJump()
{
	bPressedJump = true;
}


void AFPSCharacter::StopJump()
{
	bPressedJump = false;
}

void AFPSCharacter::Fire()
{
	if (ProjectileClass)
	{
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);

		FRotator MuzzleRotation = CameraRotation;

		MuzzleRotation.Pitch += 10.0f;

		UWorld* World = GetWorld();

		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);

			if (Projectile)
			{
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	
	
	}


}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

UCLASS()
class FPSPROJECT_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float Fire_Timer = 0.0f;
	bool bOnfire = false;


	// 전후 이동 처리
	UFUNCTION()
	void MoveForward(float value);

	// 좌우 이동 처리
	UFUNCTION()
	void MoveRight(float value);

	//UFUNCTION 매크로는 엔진에게 이 함수들을 인식시켜 시리얼라이제이션, 최적화
	// 기타 엔진 함수성에 포함될 수 있도록 한다.


	// 키를 누르면 점프 플래그를 설정합니다.
	UFUNCTION()
	void StartJump();

	// 키를 떼면 점프 플래그를 지웁니다.
	UFUNCTION()
	void StopJump();


	// FPS 카메라
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* FPSCameraComponent;

	// 일인칭 메시(팔), 소유 플레이어에게만 보입니다
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	class USkeletalMeshComponent* FPSMesh;


	UFUNCTION()
	void Fire();

	UFUNCTION()
	void FireStop();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GamePlay")
	FVector MuzzleOffset;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<class AFPSProjectile> ProjectileClass;



};

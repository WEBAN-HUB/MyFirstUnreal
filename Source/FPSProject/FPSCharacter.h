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


	// ���� �̵� ó��
	UFUNCTION()
	void MoveForward(float value);

	// �¿� �̵� ó��
	UFUNCTION()
	void MoveRight(float value);

	//UFUNCTION ��ũ�δ� �������� �� �Լ����� �νĽ��� �ø���������̼�, ����ȭ
	// ��Ÿ ���� �Լ����� ���Ե� �� �ֵ��� �Ѵ�.


	// Ű�� ������ ���� �÷��׸� �����մϴ�.
	UFUNCTION()
	void StartJump();

	// Ű�� ���� ���� �÷��׸� ����ϴ�.
	UFUNCTION()
	void StopJump();


	// FPS ī�޶�
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* FPSCameraComponent;

	// ����Ī �޽�(��), ���� �÷��̾�Ը� ���Դϴ�
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

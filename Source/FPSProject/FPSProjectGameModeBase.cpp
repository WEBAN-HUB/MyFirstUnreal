// Copyright Epic Games, Inc. All Rights Reserved.


#include "FPSProjectGameModeBase.h"

void AFPSProjectGameModeBase::StartPlay()
{
	Super::StartPlay();

	if (GEngine) 
	{
		// ����� �޽����� 5�ʰ� ǥ���մϴ�.
		// "Ű" (ù ��° �μ�) ���� -1�� �ϸ� �� �޽����� ���� ������Ʈ�ϰų� ���ΰ�ĥ �ʿ䰡 ������ ��Ÿ���ϴ�.
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("I must do this project!"));


	}


}
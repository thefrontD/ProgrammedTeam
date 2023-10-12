// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MobTypeEnum.h"
#include "PTSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAMMEDTEAM_API UPTSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPTSaveGame();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<MobType> SavedMobTypes;
};

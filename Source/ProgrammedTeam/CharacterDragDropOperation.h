// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "MobTypeEnum.h"
#include "CharacterDragDropOperation.generated.h"


/**
 * 
 */
UCLASS()
class PROGRAMMEDTEAM_API UCharacterDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		MobType MobTypeValue;
};

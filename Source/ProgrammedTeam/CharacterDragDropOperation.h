// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "CharacterDragDropOperation.generated.h"


UENUM(BlueprintType)
enum class MobType : uint8 {
	None,
	Pistol,
	AssultRifle,
	SniperRifle,
	Max
};
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

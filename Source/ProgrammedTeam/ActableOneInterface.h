// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ActableOneInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UActableOneInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROGRAMMEDTEAM_API IActableOneInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void BeginActionA() PURE_VIRTUAL(IActableOneInterface::BeginActionA)
	virtual void BeginActionB() PURE_VIRTUAL(IActableOneInterface::BeginActionB)
	virtual void BeginActionC() PURE_VIRTUAL(IActableOneInterface::BeginActionC)
};

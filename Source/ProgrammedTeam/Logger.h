// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(GPC, Log, All)

#define DEFAULT_KEY      (INDEX_NONE)
#define DEFAULT_DURATION (5.0f)
#define DEFAULT_COLOR    (FColor::Cyan)

/**
 * 
 */
class PROGRAMMEDTEAM_API Logger
{
public:
    static void Log(int32    const& Data);
    static void Log(float    const& Data);
    static void Log(FString  const& Data);
    static void Log(FVector  const& Data);
    static void Log(FRotator const& Data);
    static void Log(UObject* const& Data);

    static void Print(int32    const& Data, int32 const Key = DEFAULT_KEY, float const Duration = DEFAULT_DURATION, FColor const Color = DEFAULT_COLOR);
    static void Print(float    const& Data, int32 const Key = DEFAULT_KEY, float const Duration = DEFAULT_DURATION, FColor const Color = DEFAULT_COLOR);
    static void Print(FString  const& Data, int32 const Key = DEFAULT_KEY, float const Duration = DEFAULT_DURATION, FColor const Color = DEFAULT_COLOR);
    static void Print(FVector  const& Data, int32 const Key = DEFAULT_KEY, float const Duration = DEFAULT_DURATION, FColor const Color = DEFAULT_COLOR);
    static void Print(FRotator const& Data, int32 const Key = DEFAULT_KEY, float const Duration = DEFAULT_DURATION, FColor const Color = DEFAULT_COLOR);
    static void Print(UObject* const& Data, int32 const Key = DEFAULT_KEY, float const Duration = DEFAULT_DURATION, FColor const Color = DEFAULT_COLOR);

};

#undef DEFAULT_KEY
#undef DEFAULT_DURATION
#undef DEFAULT_COLOR
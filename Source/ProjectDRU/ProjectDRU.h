// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogProjectDRU, Log, All);

#define ABCHECK(Expr, ...) if(!(Expr)) {UE_LOG(LogProjectDRU, Error, TEXT("ASSERT : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__;}

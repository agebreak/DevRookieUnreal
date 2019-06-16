// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogProjectDRU, Log, All);

#define ABCHECK(Expr, ...) if(!(Expr)) {UE_LOG(LogProjectDRU, Error, TEXT("ASSERT : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__;}
#define ABLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))			// 로그를 사용한 함수의 실점지점을 파악할 때 유용한 로그 매크로
#define ABLOG_S(Verbosity) UE_LOG(LogProjectDRU, Verbosity, TEXT("%s"), *ABLOG_CALLINFO)					// 정보에 형식 문자열로 추가 정보를 지정해 로그를 남김.
#define ABLOG(Verbosity, Format, ...) UE_LOG(LogProjectDRU, Verbosity, TEXT("%s %s"), *ABLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

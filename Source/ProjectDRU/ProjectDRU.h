// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogProjectDRU, Log, All);

#define ABCHECK(Expr, ...) if(!(Expr)) {UE_LOG(LogProjectDRU, Error, TEXT("ASSERT : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__;}
#define ABLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))			// �α׸� ����� �Լ��� ���������� �ľ��� �� ������ �α� ��ũ��
#define ABLOG_S(Verbosity) UE_LOG(LogProjectDRU, Verbosity, TEXT("%s"), *ABLOG_CALLINFO)					// ������ ���� ���ڿ��� �߰� ������ ������ �α׸� ����.
#define ABLOG(Verbosity, Format, ...) UE_LOG(LogProjectDRU, Verbosity, TEXT("%s %s"), *ABLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

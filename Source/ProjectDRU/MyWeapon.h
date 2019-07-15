// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectDRU.h"
#include "GameFramework/Actor.h"
#include "MyWeapon.generated.h"

UCLASS()
class PROJECTDRU_API AMyWeapon : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AMyWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	USkeletalMeshComponent* Weapon;
};

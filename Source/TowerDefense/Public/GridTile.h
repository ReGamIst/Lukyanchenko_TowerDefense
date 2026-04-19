// GridTile.h
#pragma once

#include "CoreMinimal.h"
#include "GridTile.generated.h"

USTRUCT(BlueprintType)
struct FGridTile
{
	GENERATED_BODY()

	// Existing properties (you may already have these)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	FVector WorldLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	int32 GridX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	int32 GridY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	bool bIsOccupied;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	float TileHeight;

	// NEW: Void tile property
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	bool bIsVoidTile;

	// Constructor
	FGridTile()
		: WorldLocation(FVector::ZeroVector)
		, GridX(0)
		, GridY(0)
		, bIsOccupied(false)
		, TileHeight(0.0f)
		, bIsVoidTile(false)  // Default: not void
	{
	}
};
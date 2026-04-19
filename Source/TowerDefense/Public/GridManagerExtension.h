// GridManagerExtension.h
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GridTile.h"
#include "GridManagerExtension.generated.h"

/**
 * Extension component for Grid Manager
 * Handles void tiles and other C++ grid functionality
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOWERDEFENSE_API UGridManagerExtension : public UActorComponent
{
	GENERATED_BODY()

public:
	UGridManagerExtension();

	// Initialize with grid reference
	UFUNCTION(BlueprintCallable, Category = "Grid|Void")
	void Initialize(UPARAM(ref) TArray<FGridTile>& InTileGrid);

	// Mark a tile as void
	UFUNCTION(BlueprintCallable, Category = "Grid|Void")
	bool SetTileVoid(int32 TileIndex, bool bIsVoid);

	// Check if a tile is void
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Grid|Void")
	bool IsTileVoid(int32 TileIndex) const;

	// Get all void tile indices
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Grid|Void")
	TArray<int32> GetAllVoidTiles() const;

	// Set multiple tiles as void at once
	UFUNCTION(BlueprintCallable, Category = "Grid|Void")
	void SetMultipleTilesVoid(const TArray<int32>& TileIndices, bool bIsVoid);

	// Check if position is over void tile
	UFUNCTION(BlueprintCallable, Category = "Grid|Void")
	bool IsWorldLocationOverVoid(const FVector& WorldLocation, float Tolerance = 50.0f) const;

protected:
	virtual void BeginPlay() override;

private:
	// Pointer to the tile grid (owned by BP_GridManager)
	TArray<FGridTile>* TileGridPtr;

	// Cached grid dimensions
	int32 GridWidth;
	int32 GridHeight;

	// Helper: Validate tile index
	bool IsValidTileIndex(int32 Index) const;
};
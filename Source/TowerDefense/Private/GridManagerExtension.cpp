// GridManagerExtension.cpp
#include "GridManagerExtension.h"

UGridManagerExtension::UGridManagerExtension()
{
    PrimaryComponentTick.bCanEverTick = false;
    TileGridPtr = nullptr;
    GridWidth = 0;
    GridHeight = 0;
}

void UGridManagerExtension::BeginPlay()
{
    Super::BeginPlay();
}

void UGridManagerExtension::Initialize(UPARAM(ref) TArray<FGridTile>& InTileGrid)
{
    TileGridPtr = &InTileGrid;
    
    if (TileGridPtr && TileGridPtr->Num() > 0)
    {
        // Calculate grid dimensions from first tile
        // Assumes tiles are ordered and grid is rectangular
        int32 MaxX = 0;
        int32 MaxY = 0;
        
        for (const FGridTile& Tile : *TileGridPtr)
        {
            if (Tile.GridX > MaxX) MaxX = Tile.GridX;
            if (Tile.GridY > MaxY) MaxY = Tile.GridY;
        }
        
        GridWidth = MaxX + 1;
        GridHeight = MaxY + 1;
        
        UE_LOG(LogTemp, Log, TEXT("GridManagerExtension initialized: %dx%d grid, %d tiles"), 
               GridWidth, GridHeight, TileGridPtr->Num());
    }
}

bool UGridManagerExtension::SetTileVoid(int32 TileIndex, bool bIsVoid)
{
    if (!IsValidTileIndex(TileIndex))
    {
        UE_LOG(LogTemp, Warning, TEXT("SetTileVoid: Invalid tile index %d"), TileIndex);
        return false;
    }

    (*TileGridPtr)[TileIndex].bIsVoidTile = bIsVoid;
    
    UE_LOG(LogTemp, Log, TEXT("Tile %d set to void: %s"), 
           TileIndex, bIsVoid ? TEXT("true") : TEXT("false"));
    
    return true;
}

bool UGridManagerExtension::IsTileVoid(int32 TileIndex) const
{
    if (!IsValidTileIndex(TileIndex))
    {
        return false;
    }

    return (*TileGridPtr)[TileIndex].bIsVoidTile;
}

TArray<int32> UGridManagerExtension::GetAllVoidTiles() const
{
    TArray<int32> VoidTiles;
    
    if (!TileGridPtr)
    {
        return VoidTiles;
    }

    for (int32 i = 0; i < TileGridPtr->Num(); ++i)
    {
        if ((*TileGridPtr)[i].bIsVoidTile)
        {
            VoidTiles.Add(i);
        }
    }

    return VoidTiles;
}

void UGridManagerExtension::SetMultipleTilesVoid(const TArray<int32>& TileIndices, bool bIsVoid)
{
    for (int32 Index : TileIndices)
    {
        SetTileVoid(Index, bIsVoid);
    }
    
    UE_LOG(LogTemp, Log, TEXT("Set %d tiles to void: %s"), 
           TileIndices.Num(), bIsVoid ? TEXT("true") : TEXT("false"));
}

bool UGridManagerExtension::IsWorldLocationOverVoid(const FVector& WorldLocation, float Tolerance) const
{
    if (!TileGridPtr)
    {
        return false;
    }

    // Find closest tile to this world location
    float ClosestDistance = FLT_MAX;
    int32 ClosestTileIndex = -1;

    for (int32 i = 0; i < TileGridPtr->Num(); ++i)
    {
        const FGridTile& Tile = (*TileGridPtr)[i];
        
        // 2D distance (ignore Z)
        float Distance = FVector::Dist2D(WorldLocation, Tile.WorldLocation);
        
        if (Distance < ClosestDistance)
        {
            ClosestDistance = Distance;
            ClosestTileIndex = i;
        }
    }

    if (ClosestTileIndex == -1 || ClosestDistance > Tolerance)
    {
        return false;
    }

    return (*TileGridPtr)[ClosestTileIndex].bIsVoidTile;
}

bool UGridManagerExtension::IsValidTileIndex(int32 Index) const
{
    return TileGridPtr && Index >= 0 && Index < TileGridPtr->Num();
}